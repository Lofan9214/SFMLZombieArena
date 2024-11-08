#include "stdafx.h"
#include "ItemGenerator.h"
#include "Item.h"
#include "UiUpgrade.h"
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
	if (!active)
		return;

	ammoTimer += dt;
	healthTimer += dt;

	if (ammoTimer > ammoDelay)
	{
		ammoTimer = 0.f;
		sceneGame->SpawnItem(Upgrade::AmmoPickups, ammo);
	}
	if (healthTimer > healthDelay)
	{
		healthTimer = 0.f;
		sceneGame->SpawnItem(Upgrade::HealthPickups, health);
	}
}

void ItemGenerator::FixedUpdate(float dt)
{
}

void ItemGenerator::Draw(sf::RenderWindow& window)
{
}

void ItemGenerator::UpgradeItem(Upgrade type)
{
	switch (type)
	{
	case Upgrade::HealthPickups:
		health += 5;
		healthDelay *= 0.95f;
		break;
	case Upgrade::AmmoPickups:
		ammo += 5;
		ammoDelay *= 0.95f;
		break;
	default:
		break;
	}
}

float ItemGenerator::GetItemDelay(Upgrade type)
{
	switch (type)
	{
	case Upgrade::HealthPickups:
		return healthDelay;
		break;
	case Upgrade::AmmoPickups:
		return ammoDelay;
		break;
	}
	return 0.0f;
}

int ItemGenerator::GetItemQt(Upgrade type)
{
	switch (type)
	{
	case Upgrade::HealthPickups:
		return health;
		break;
	case Upgrade::AmmoPickups:
		return ammo;
		break;
	}
	return 0;
}

void ItemGenerator::SetItemDelay(Upgrade type, float value)
{
	switch (type)
	{
	case Upgrade::HealthPickups:
		healthDelay = value;
		break;
	case Upgrade::AmmoPickups:
		ammoDelay = value;
		break;
	}
}

void ItemGenerator::SetItemQt(Upgrade type, float value)
{
	switch (type)
	{
	case Upgrade::HealthPickups:
		health = value;
		break;
	case Upgrade::AmmoPickups:
		ammo = value;
		break;
	}
}
