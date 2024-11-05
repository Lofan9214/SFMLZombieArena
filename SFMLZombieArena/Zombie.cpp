#include "stdafx.h"
#include "Zombie.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Zombie::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Zombie::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Zombie::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetType(type);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<Player*>(sceneGame->FindGo("Player"));
	body.setTexture(TEXTURE_MGR.Get(textureId));

	SetOrigin(Origins::MC);
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);
	SetScale({ 1.f,1.f });

	movableBounds = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("TileMap"))->GetMovableBounds();
	sf::FloatRect zombieRect = GetLocalBounds();
	movableBounds.left += zombieRect.width * 0.5f;
	movableBounds.width -= zombieRect.width;
	movableBounds.top += zombieRect.height * 0.5f;
	movableBounds.height -= zombieRect.height;
}

void Zombie::LateUpdate(float dt)
{
}

void Zombie::Update(float dt)
{
	if (player != nullptr && Utils::Distance(position, player->GetPosition()) > 10.f)
	{
		direction = Utils::GetNormal(player->GetPosition() - position);
		SetRotation(Utils::Angle(direction));
		sf::Vector2f newpos = position + direction * speed * dt;
		if (newpos.y < movableBounds.top)
		{
			newpos.y = movableBounds.top;
		}
		else if (newpos.y > movableBounds.top + movableBounds.height)
		{
			newpos.y = movableBounds.top + movableBounds.height;
		}
		if (newpos.x < movableBounds.left)
		{
			newpos.x = movableBounds.left;
		}
		else if (newpos.x > movableBounds.left + movableBounds.width)
		{
			newpos.x = movableBounds.left + movableBounds.width;
		}
		SetPosition(newpos);
		SetPosition(position + direction * speed * dt);
	}
	debugBox.SetBounds(GetGlobalBounds());
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	debugBox.Draw(window);
}

void Zombie::FixedUpdate(float dt)
{
	if (sceneGame == nullptr)
		return;

	debugBox.SetOutlineColor(sf::Color::Green);

	sf::FloatRect bounds = GetGlobalBounds();
	sf::FloatRect playerBounds = player->GetGlobalBounds();

	if (bounds.intersects(playerBounds))
	{
		debugBox.SetOutlineColor(sf::Color::Red);
		player->OnDamage(damage);
	}
}

void Zombie::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Bloater:
		textureId = "graphics/bloater.png";
		speed = 100.f;
		maxHp = 50;

		break;
	case Types::Chaser:
		textureId = "graphics/chaser.png";
		speed = 75.f;
		maxHp = 20;

		break;
	case Types::Crawler:
		textureId = "graphics/crawler.png";
		speed = 50.f;
		maxHp = 10;

		break;
	default:
		break;
	}
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(originPreset);

	hp = maxHp;
}

void Zombie::OnDamage(int d)
{
	hp -= d;
	if (hp <= 0 && sceneGame != nullptr)
	{
		sceneGame->OnZombieDie(this);
	}
}
