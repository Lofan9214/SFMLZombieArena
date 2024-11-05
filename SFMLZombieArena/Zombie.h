#pragma once

class Player;
class SceneGame;

class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};

	static const int TotalTypes = 3;

	DebugBox debugBox;

protected:
	Types type = Types::Bloater;
	sf::Sprite body;
	sf::String textureId;

	sf::Vector2f direction;

	int maxHp = 0;
	float speed = 0.f;
	int damage = 0;
	float attackInterval = 0.f;

	int hp = 0;
	float attackTimer = 0.f;

	Player* player = nullptr;
	sf::FloatRect movableBounds;
	SceneGame* sceneGame = nullptr;

public:
	Zombie(const std::string& name = "");
	~Zombie() = default;

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

	void SetType(Types type);

	void OnDamage(int damage);
};
