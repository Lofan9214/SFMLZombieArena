#pragma once

class SceneGame;
class BombIcon;
enum class Upgrade;

class Player : public GameObject
{
protected:

	sf::Sprite body;
	std::string textureId = "graphics/player.png";

	std::string shootSBId = "sound/shoot.wav";
	std::string reloadSBId = "sound/reload.wav";
	std::string hitSBId = "sound/hit.wav";

	sf::Vector2f direction;
	sf::Vector2f look;

	float speed = 500.f;

	SceneGame* sceneGame;

	int hp = 100;
	int maxHp = 100;
	int ammo = 10;
	int totalAmmo = 150;
	int clip = 15;

	float shootTimer = 0.5f;
	float shootDelay = 0.5f;
	float reloadTimer = 0.f;
	float reloadDelay = 1.f;
	float damageTimer = 0.f;
	float damageDelay = 1.f;
	float bombTimer = 1.5f;
	float bombDelay = 1.5f;

	bool isReloading = false;
	bool isDamaged = false;

	sf::FloatRect movableBounds;

	BombIcon* bombIcon;

	DebugBox debugBox;

public:
	Player(const std::string& name = "");
	~Player() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override { return body.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() const override { return body.getGlobalBounds(); }

	void SetMovableBounds(const sf::FloatRect& bounds);

	void Init() override;
	void Release() override;
	void Reset() override;
	void LateUpdate(float dt) override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Shoot();
	void Reload();

	void OnHealth(int hp);
	void OnAmmo(int ammo);
	void OnDamage(int d);

	int GetTotalAmmo() { return totalAmmo; }
	int GetAmmo() { return ammo; }
	int GetHp() { return hp; }
	int GetMaxHp() { return maxHp; }
	void UpgradeStat(Upgrade upgrade);

	void SetBombIcon(BombIcon* bombicon) { bombIcon = bombicon; }
};
