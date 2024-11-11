#pragma once

#include "BombIcon.h"
#include "TextGo.h"

class TextGo;

class UiHud : public GameObject
{
protected:

	TextGo textScore;
	TextGo textHiScore;

	sf::Sprite iconAmmoIcon;

	TextGo textAmmo;
	sf::RectangleShape gaugeHp;
	TextGo textWave;
	TextGo textZombieCount;

	BombIcon bombicon;

	sf::Vector2f gaugeHpMaxSize = { 400.f,50.f };


public:
	UiHud(const std::string& name = "");
	~UiHud() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void LateUpdate(float dt) override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetScore(int s);
	void SetHighScore(int s);
	void SetAmmo(int current, int total);
	void SetHp(int hp, int max);
	void SetWave(int w);
	void SetZombieCount(int count);

	BombIcon* GetBombIcon() { return &bombicon; }
};
