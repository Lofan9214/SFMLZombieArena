#include "stdafx.h"
#include "Blood.h"
#include "SceneGame.h"

Blood::Blood(const std::string& name)
	: GameObject(name)
{
}

void Blood::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Blood::SetRotation(float angle)
{
	rotation = angle;
}

void Blood::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Blood::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Blood::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Blood::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Blood::Release()
{
}

void Blood::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::MC);
	timer = 0.f;
	duration = 10.f;
	active = true;
}

void Blood::LateUpdate(float dt)
{
}

void Blood::Update(float dt)
{
	timer += dt;
	if (timer > duration && sceneGame!=nullptr)
	{
		sceneGame->ReturnBlood(this);
	}
}

void Blood::FixedUpdate(float dt)
{
}

void Blood::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
