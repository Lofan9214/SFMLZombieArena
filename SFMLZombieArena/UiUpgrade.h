#pragma once

enum class Upgrade
{
	RateOfFire,
	ClipSize,
	MaxHealth,
	RunSpeed,
	HealthPickups,
	AmmoPickups,
	Count,
};

class SceneGame;

class UiUpgrade : public GameObject
{
protected:
	std::vector<sf::Text> upgrades;
	sf::Sprite background;

	SceneGame* sceneGame;
	float timer;

public:
	UiUpgrade(const std::string& name = "");
	~UiUpgrade() = default;

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
};
