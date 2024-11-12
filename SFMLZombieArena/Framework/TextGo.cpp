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

void TextGo::SetFont(const std::string& fontid)
{
	fontId = fontid;
	sf::Font& font = FONT_MGR.Get(fontId);
	SetFont(font);
}

void TextGo::SetFont(const sf::Font& font)
{
	text.setFont(font);
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
	SetString(stringId);
}

void TextGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	text.setPosition(pos);
}



void TextGo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	text.setScale(scale);
}

sf::FloatRect TextGo::GetLocalBounds() const
{
	return text.getLocalBounds();
}

sf::FloatRect TextGo::GetGlobalBounds() const
{
	return text.getGlobalBounds();
}

void TextGo::LateUpdate(float dt)
{
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
	rotation = angle;
	text.setRotation(angle);
}

void TextGo::SetString(const std::string& str)
{
	stringId = str;
	text.setString(STRING_TABLE->Get(stringId));

	//text.setString(id)

	if (originPreset < Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}

void TextGo::SetString(const std::string& id, const std::string& str)
{
	if (id != "")
	{
		stringId = id;

		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

		text.setString(STRING_TABLE->Get(stringId) + converter.from_bytes(str));
	}
	else
	{
		stringId = id;
		text.setString(str);
	}

	if (originPreset < Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}

void TextGo::SetFillColor(sf::Color color)
{
	text.setFillColor(color);
}

void TextGo::SetCharSize(int size)
{
	text.setCharacterSize(size);
}

void TextGo::OnLocalize(Languages lang)
{
	text.setString(STRING_TABLE->Get(stringId));
	if (originPreset < Origins::Custom)
	{
		SetOrigin(originPreset);
	}
}
