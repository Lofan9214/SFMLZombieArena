#include "stdafx.h"
#include "ItemGenerator.h"
#include "SceneGame.h"

ItemGenerator::ItemGenerator(const std::string& name)
	: GameObject(name)
{
}

void ItemGenerator::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void ItemGenerator::SetRotation(float angle)
{
	rotation = angle;
}

void ItemGenerator::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void ItemGenerator::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void ItemGenerator::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void ItemGenerator::Init()
{
}

void ItemGenerator::Release()
{
}

void ItemGenerator::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	health = 10;
	ammo = 15;

	ammoTimer = 0.f;
	ammoDelay = 10.f;
	healthTimer = 0.f;
	healthDelay = 10.f;
}

void ItemGenerator::LateUpdate(float dt)
{
}

void ItemGenerator::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::O))
	{
		active = !active;
		ammoTimer = 0.f;
		healthTimer = 0.f;
	}
	if (active)
	{
		ammoTimer += dt;
		healthTimer += dt;

		if (ammoTimer > ammoDelay)
		{
			ammoTimer = 0.f;
			sceneGame->SpawnItem(Item::Types::Ammo,ammo);
		}
		if (healthTimer > healthDelay)
		{
			healthTimer = 0.f;
			sceneGame->SpawnItem(Item::Types::Health,health);
		}
	}
}

void ItemGenerator::FixedUpdate(float dt)
{
}

void ItemGenerator::Draw(sf::RenderWindow& window)
{
}

void ItemGenerator::Upgrade(Item::Types type)
{
	switch (type)
	{
	case Item::Types::Health:
		health += 5;
		healthDelay *= 0.95f;
		break;
	case Item::Types::Ammo:
		ammo += 5;
		ammoDelay *= 0.95f;

		break;
	default:
		break;
	}
}
