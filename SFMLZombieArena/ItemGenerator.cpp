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
}

void ItemGenerator::LateUpdate(float dt)
{
}

void ItemGenerator::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::O))
	{
		active = !active;
		generatorTimer = 0.f;
	}
	if (active)
	{
		generatorTimer += dt;
		if (generatorTimer > generatorDelay)
		{
			generatorTimer = 0.f;
			sceneGame->SpawnItem();
		}
	}

}

void ItemGenerator::FixedUpdate(float dt)
{
}

void ItemGenerator::Draw(sf::RenderWindow& window)
{
}
