#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "SceneGame.h"
#include "UiUpgrade.h"

Item::Item(const std::string& name)
	: GameObject(name),type(Upgrade::HealthPickups)
{
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Item::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Item::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Item::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Item::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Item::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetType(type, 0);
}

void Item::Release()
{
}

void Item::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<Player*>(sceneGame->FindGo("Player"));
	body.setTexture(TEXTURE_MGR.Get(textureId));

	value = 0;
	SetOrigin(Origins::MC);
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);
	SetScale({ 1.f,1.f });
}

void Item::LateUpdate(float dt)
{
}

void Item::Update(float dt)
{
	debugBox.SetOutlineColor(sf::Color::Green);
	debugBox.SetBounds(GetGlobalBounds());
	hitBox.UpdateTr(body, body.getLocalBounds());
}

void Item::FixedUpdate(float dt)
{
	sf::FloatRect bodyRect = GetGlobalBounds();
	sf::FloatRect playerRect = player->GetGlobalBounds();

	if (bodyRect.intersects(playerRect) && Utils::CheckCollision(hitBox, player->GetHitBox()))
	{
		switch (type)
		{
		case Upgrade::HealthPickups:
			player->OnHealth(value);
			break;
		case Upgrade::AmmoPickups:
			player->OnAmmo(value);
			break;
		default:
			break;
		}
		sceneGame->OnItemTake(this);
	}
	debugBox.SetBounds(GetGlobalBounds());
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	debugBox.Draw(window);
}

void Item::SetType(Upgrade type, int v)
{
	this->type = type;
	switch (this->type)
	{
	case Upgrade::HealthPickups:
		textureId = "graphics/health_pickup.png";
		value = v;

		break;
	case Upgrade::AmmoPickups:
		textureId = "graphics/ammo_pickup.png";
		value = v;

		break;
	default:
		break;
	}
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(originPreset);
}
