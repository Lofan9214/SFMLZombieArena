#include "stdafx.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Bullet::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Bullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Bullet::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::ML);

	SetPosition({ 0.f,0.f });
	SetRotation(0.f);
	SetScale({ 1.5f,1.5f });

	direction = { 0.f,0.f };
	speed = 0;
	damage = 25;
}

void Bullet::LateUpdate(float dt)
{
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);

	debugBox.SetBounds(GetGlobalBounds());
	hitBox.UpdateTr(body, GetLocalBounds());
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	debugBox.Draw(window);
}


void Bullet::FixedUpdate(float dt)
{
	if (sceneGame == nullptr)
		return;

	debugBox.SetOutlineColor(sf::Color::Green);
	const auto& list = sceneGame->GetZombieList();
	for (auto zombie : list)
	{
		if (!zombie->IsActive())
			continue;

		sf::FloatRect bounds = GetGlobalBounds();
		sf::FloatRect zombieBounds = zombie->GetGlobalBounds();

		if (bounds.intersects(zombieBounds)&&Utils::CheckCollision(GetHitBox(), zombie->GetHitBox()))
		{
			debugBox.SetOutlineColor(sf::Color::Red);
			zombie->OnDamage(damage);
			sceneGame->ReturnBullet(this);
			break;
		}
	}
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d)
{
	SetPosition(pos);
	direction = dir;
	speed = s;
	damage = d;

	SetRotation(Utils::Angle(direction));
}