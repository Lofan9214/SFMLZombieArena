#include "stdafx.h"
#include "UiGameMessage.h"

UiGameMessage::UiGameMessage(const std::string& name)
	: GameObject(name)
{
}

void UiGameMessage::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiGameMessage::SetRotation(float angle)
{
	rotation = angle;
}

void UiGameMessage::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiGameMessage::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiGameMessage::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiGameMessage::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 2;
}

void UiGameMessage::Release()
{
}

void UiGameMessage::Reset()
{
	float textSize = 150.f;
	sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");
	sf::Vector2f pos = FRAMEWORK.GetWindowSizef() * 0.5f;

	textGameOver.setString("PRESS ENTER\nTO CONTINUE");
	textGameOver.setFont(font);
	textGameOver.setCharacterSize(textSize);
	textGameOver.setFillColor(sf::Color::White);
	Utils::SetOrigin(textGameOver, Origins::MC);
	textGameOver.setPosition(pos);

	textGameStart.setString("PRESS ENTER\nTO START");
	textGameStart.setFont(font);
	textGameStart.setCharacterSize(textSize);
	textGameStart.setFillColor(sf::Color::White);
	Utils::SetOrigin(textGameStart, Origins::MC);
	textGameStart.setPosition(pos);
}

void UiGameMessage::LateUpdate(float dt)
{
}

void UiGameMessage::Update(float dt)
{
}

void UiGameMessage::FixedUpdate(float dt)
{
}

void UiGameMessage::Draw(sf::RenderWindow& window)
{
	if (isGameOver)
	{
		window.draw(textGameOver);
	}
	else
	{
		window.draw(textGameStart);
	}
}

void UiGameMessage::SetStat(bool isGameOver)
{
	this->isGameOver = isGameOver;
}
