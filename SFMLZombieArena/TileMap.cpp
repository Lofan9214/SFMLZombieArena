#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void TileMap::SetRotation(float angle)
{
	rotation = angle;
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void TileMap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void TileMap::Init()
{
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
}

void TileMap::UpdateTransform()
{
}
