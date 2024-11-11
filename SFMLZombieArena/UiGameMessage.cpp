#include "stdafx.h"
#include "UiGameMessage.h"
#include "TextGo.h"

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

	textGameOver = new TextGo();
	textGameStart = new TextGo();
}

void UiGameMessage::Release()
{
	delete textGameOver;
	delete textGameStart;
}

void UiGameMessage::Reset()
{
	float textSize = 150.f;
	sf::Font& font = FONT_MGR.Get("fonts/malgun.ttf");
	sf::Vector2f pos = FRAMEWORK.GetWindowSizef() * 0.5f;
	
	textGameOver->Reset();
	textGameOver->SetString("GameOverMessage");
	textGameOver->SetFont(font);
	textGameOver->SetCharSize(textSize);
	textGameOver->SetFillColor(sf::Color::White);
	textGameOver->SetOrigin(Origins::MC);
	textGameOver->SetPosition(pos);

	textGameStart->Reset();
	textGameStart->SetString("StartMessage");
	textGameStart->SetFont(font);
	textGameStart->SetCharSize(textSize);
	textGameStart->SetFillColor(sf::Color::White);
	textGameStart->SetOrigin(Origins::MC);
	textGameStart->SetPosition(pos);
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
		textGameOver->Draw(window);
	}
	else
	{
		textGameStart->Draw(window);
	}
}

void UiGameMessage::SetStat(bool isGameOver)
{
	this->isGameOver = isGameOver;
}
