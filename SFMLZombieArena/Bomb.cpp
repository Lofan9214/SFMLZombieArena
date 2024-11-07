#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb(const std::string& name)
	: GameObject(name)
{
}

void Bomb::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void Bomb::SetRotation(float angle)
{
	rotation = angle;
}

void Bomb::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Bomb::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void Bomb::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void Bomb::Init()
{
}

void Bomb::Release()
{
}

void Bomb::Reset()
{
}

void Bomb::Update(float dt)
{
}

void Bomb::Draw(sf::RenderWindow& window)
{
}
