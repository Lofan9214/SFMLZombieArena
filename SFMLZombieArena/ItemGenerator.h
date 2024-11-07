#pragma once

class SceneGame;
enum class Upgrade;

class ItemGenerator : public GameObject
{
protected:
	SceneGame* sceneGame;

	int health = 10;
	int ammo = 15;

	float ammoTimer = 0.f;
	float ammoDelay = 10.f;
	float healthTimer = 0.f;
	float healthDelay = 10.f;
public:
	ItemGenerator(const std::string& name = "");
	~ItemGenerator() = default;

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

	void UpgradeItem(Upgrade type);
};
