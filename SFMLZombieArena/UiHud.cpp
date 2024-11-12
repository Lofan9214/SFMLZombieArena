#include "stdafx.h"
#include "UiHud.h"
#include "TextGo.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiHud::SetRotation(float angle)
{
	rotation = angle;
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiHud::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiHud::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

}

void UiHud::Release()
{
}

void UiHud::Reset()
{

	float textSize = 50.f;

	sf::Font& font = FONT_MGR.Get("fonts/malgun.ttf");
	textScore.SetFont(font);
	textScore.SetCharSize(textSize);
	textScore.SetFillColor(sf::Color::White);
	textScore.SetOrigin(Origins::TL);

	textHiScore.SetFont(font);
	textHiScore.SetCharSize(textSize);
	textHiScore.SetFillColor(sf::Color::White);
	textHiScore.SetOrigin(Origins::TR);

	textAmmo.SetFont(font);
	textAmmo.SetCharSize(textSize);
	textAmmo.SetFillColor(sf::Color::White);
	textAmmo.SetOrigin(Origins::BL);

	textWave.SetFont(font);
	textWave.SetCharSize(textSize);
	textWave.SetFillColor(sf::Color::White);
	textWave.SetOrigin(Origins::BR);

	textZombieCount.SetFont(font);
	textZombieCount.SetCharSize(textSize);
	textZombieCount.SetFillColor(sf::Color::White);
	textZombieCount.SetOrigin(Origins::BR);

	gaugeHp.setFillColor(sf::Color::Red);
	gaugeHp.setSize(gaugeHpMaxSize);
	Utils::SetOrigin(gaugeHp, Origins::BL);

	iconAmmoIcon.setTexture(TEXTURE_MGR.Get("graphics/ammo_icon.png"));
	Utils::SetOrigin(iconAmmoIcon, Origins::BL);

	bombicon.Reset();
	bombicon.SetOrigin(Origins::BL);

	float topY = 25.f;
	sf::Vector2f size = FRAMEWORK.GetWindowSizef();
	float bottomY = size.y - 25.f;

	textScore.SetPosition({ 25.f, topY });
	textHiScore.SetPosition({ size.x - 25.f, topY });

	iconAmmoIcon.setPosition(25.f, bottomY);
	bombicon.SetPosition({ 300.f, bottomY });
	gaugeHp.setPosition(380.f, bottomY);

	textAmmo.SetPosition({ 100.f, bottomY });
	textWave.SetPosition({ size.x - 400.f, bottomY });
	textZombieCount.SetPosition({ size.x - 25.f, bottomY });
	SetScore(0);
	SetHighScore(0);
	SetAmmo(0, 0);
	SetHp(1, 1);
	SetWave(0);
	SetZombieCount(0);
}

void UiHud::LateUpdate(float dt)
{
}

void UiHud::Update(float dt)
{
	bombicon.Update(dt);
}

void UiHud::FixedUpdate(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	textScore.Draw(window);
	textHiScore.Draw(window);
	textWave.Draw(window);
	window.draw(iconAmmoIcon);
	window.draw(gaugeHp);
	textAmmo.Draw(window);
	textZombieCount.Draw(window);
	bombicon.Draw(window);
}

void UiHud::SetScore(int s)
{
	textScore.SetString("Score", std::to_string(s));
}

void UiHud::SetHighScore(int s)
{
	textHiScore.SetString("HighScore", std::to_string(s));
}

void UiHud::SetAmmo(int current, int total)
{
	textAmmo.SetString("", std::to_string(current) + " / " + std::to_string(total));
}

void UiHud::SetHp(int hp, int max)
{
	float value = (float)hp / max;
	gaugeHp.setSize({ gaugeHpMaxSize.x * value,gaugeHpMaxSize.y });
}

void UiHud::SetWave(int w)
{
	textWave.SetString("Wave", std::to_string(w));
}

void UiHud::SetZombieCount(int count)
{
	textZombieCount.SetString("Zombies", std::to_string(count));
}

void UiHud::OnLocalize(Languages lang)
{
	textAmmo.OnLocalize(lang);
	textWave.OnLocalize(lang);
	textHiScore.OnLocalize(lang);
	textScore.OnLocalize(lang);
	textZombieCount.OnLocalize(lang);
}
