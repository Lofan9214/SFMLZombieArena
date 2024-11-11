#include "stdafx.h"
#include "UiUpgrade.h"
#include "SceneGame.h"
#include "TextGo.h"

UiUpgrade::UiUpgrade(const std::string& name)
	: GameObject(name)
{
}

void UiUpgrade::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiUpgrade::SetRotation(float angle)
{
	rotation = angle;
}

void UiUpgrade::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiUpgrade::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiUpgrade::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiUpgrade::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;

	upgrades.resize((int)Upgrade::Count);
	std::string fontid = "fonts/malgun.ttf";

	for (int i = 0;i < (int)Upgrade::Count;++i)
	{
		upgrades[i].Init();
		upgrades[i].SetFont(fontid);
		upgrades[i].SetString("Upgrade" + std::to_string(i + 1));
	}
}

void UiUpgrade::Release()
{
	int count = (int)Upgrade::Count;

	for (int i = 0; i < count; ++i)
	{
		upgrades[i].Release();
	}
}

void UiUpgrade::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));
	background.setPosition({ 0.f, 0.f });

	float textSize = 100.f;

	int count = (int)Upgrade::Count;
	for (int i = 0; i < count; ++i)
	{
		upgrades[i].Reset();
		upgrades[i].SetCharSize(textSize);
		upgrades[i].SetOrigin(Origins::ML);
		upgrades[i].SetPosition({ 200.f, (120.f * i + 1) + 200.f });
	}
}

void UiUpgrade::LateUpdate(float dt)
{
}

void UiUpgrade::Update(float dt)
{
	if (sceneGame == nullptr && !active)
	{
		timer = 0.f;
		return;
	}
	timer += FRAMEWORK.GetRealDeltaTime();
	if (timer < 1.5f)
	{
		return;
	}

	sf::Vector2f mousePos = sceneGame->ScreenToUi(InputMgr::GetMousePosition());

	for (int i = 0; i < upgrades.size();++i)
	{
		if (upgrades[i].GetGlobalBounds().contains(mousePos))
		{
			upgrades[i].SetFillColor(sf::Color::Red);
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				sceneGame->OnUpgrade((Upgrade)i);
				return;
			}
		}
		else
		{
			upgrades[i].SetFillColor(sf::Color::White);
		}
	}
}

void UiUpgrade::FixedUpdate(float dt)
{
}

void UiUpgrade::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (auto& text : upgrades)
	{
		text.Draw(window);
	}
}

void UiUpgrade::OnLocalize(Languages lang)
{
	for (auto& text : upgrades)
	{
		text.OnLocalize(lang);
	}
}
