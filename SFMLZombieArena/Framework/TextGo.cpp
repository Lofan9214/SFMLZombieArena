#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& fontId, const std::string& name)
	: GameObject(name), fontId(fontId)
{
}

void TextGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(text, originPreset);
}

void TextGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.setOrigin(origin);
}

void TextGo::Init()
{
}

void TextGo::Release()
{
}

void TextGo::Reset()
{
	text.setFont(FONT_MGR.Get(fontId));
	SetOrigin(originPreset);
}

void TextGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	text.setPosition(pos);
}

void TextGo::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	text.setScale(scale);
}

void TextGo::Update(float dt)
{
}

void TextGo::FixedUpdate(float dt)
{
}

void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}

void TextGo::SetRotation(float angle)
{
	GameObject::SetRotation(angle);
	text.setRotation(angle);
}

void TextGo::SetTextString(const std::string& str)
{
	text.setString(str);
	if (originPreset < Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}

void TextGo::SetFillColor(sf::Color color)
{
	text.setFillColor(color);
}
