#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	UpdateTransform();
}

void TileMap::SetRotation(float angle)
{
	rotation = angle;
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
	UpdateTransform();
}

void TileMap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin.x = cellCount.x * cellSize.x * ((int)preset % 3) * 0.5f;
		origin.y = cellCount.y * cellSize.y * ((int)preset / 3) * 0.5f;
		UpdateTransform();
	}
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;

	Set({ 10,10 }, { 50.f,50.f }, { 50.f,50.f });
	SetOrigin(Origins::TL);
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);

	SetOrigin(originPreset);
	SetPosition({ 0.f,0.f });
}

void TileMap::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad4))
	{
		SetPosition(position + sf::Vector2f(-10.f, 0.f));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad6))
	{
		SetPosition(position + sf::Vector2f(10.f, 0.f));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad8))
	{
		SetPosition(position + sf::Vector2f(0.f, -10.f));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad2))
	{
		SetPosition(position + sf::Vector2f(0.f, 10.f));
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad7))
	{
		SetRotation(rotation - 10.f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad9))
	{
		SetRotation(rotation + 10.f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad1))
	{
		SetScale(scale * 0.9f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad3))
	{
		SetScale(scale / 0.9f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad5))
	{
		SetOrigin(originPreset == (Origins)((int)Origins::Custom - 1) ? (Origins)0 : (Origins)((int)originPreset + 1));
	}
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates st;
	st.texture = texture;
	st.transform = transform;
	window.draw(va, st);
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size, const sf::Vector2f& tileSize)
{
	cellCount = count;
	cellSize = size;
	this->tileSize = tileSize;

	va.clear();
	va.setPrimitiveType(sf::Triangles);
	va.resize(cellCount.x * cellCount.y * 6);

	sf::Vector2f posOffset[6] =
	{
		{0.f,0.f},
		{cellSize.x,0.f},
		{cellSize.x,cellSize.y},
		{cellSize.x,cellSize.y},
		{0.f,cellSize.y},
		{0.f,0.f},
	};
	sf::Vector2f texCoord[6] =
	{
		{0.f,0.f},
		{tileSize.x,0.f},
		{tileSize.x,tileSize.y},
		{tileSize.x,tileSize.y},
		{0.f,tileSize.y},
		{0.f,0.f},
	};


	for (int j = 0;j < cellCount.y;++j)
	{
		for (int i = 0; i < cellCount.x;++i)
		{
			int texIndex = Utils::RandomRange(0, 2);

			if (i == 0 || j == 0 || i == cellCount.x - 1 || j == cellCount.y - 1)
			{
				texIndex = 3;
			}

			int tileIndex = j * cellCount.x + i;
			int vertexIndex = tileIndex * 6;
			sf::Vector2f startpos = { cellSize.x * i,cellSize.y * j };

			for (int k = 0;k < 6;++k)
			{
				va[vertexIndex + k].position = startpos + posOffset[k];
				va[vertexIndex + k].texCoords = texCoord[k];
				va[vertexIndex + k].texCoords.y += texIndex * tileSize.y;
			}
		}
	}

}

void TileMap::UpdateTransform()
{
	transform = transform.Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}
