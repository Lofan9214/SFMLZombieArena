#pragma once

class Player;
class SceneGame;
enum class Upgrade;

class Item : public GameObject
{
protected:
	Upgrade type;
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

	void SetType(Upgrade type, int v);
};

