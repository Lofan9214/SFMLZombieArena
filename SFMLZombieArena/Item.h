#pragma once

class Player;
class SceneGame;

enum class ItemTypes
{
	Health,
	Ammo,
};

class Item : public GameObject
{
public:
	const static int TotalTypes = 2;
protected:
	ItemTypes type = ItemTypes::Health;
	sf::Sprite body;
	sf::String textureId;

	int value = 0;

	Player* player;
	SceneGame* sceneGame;
	DebugBox debugBox;

public:
	Item(const std::string& name = "");
	~Item() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override { return body.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() const override { return body.getGlobalBounds(); }

	void Init() override;
	void Release() override;
	void Reset() override;
	void LateUpdate(float dt) override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(ItemTypes type, int v);
};

