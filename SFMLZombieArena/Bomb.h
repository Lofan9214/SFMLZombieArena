#pragma once

class SceneGame;
class Zombie;

class Bomb : public GameObject
{
protected:


	sf::Sprite bomb;
	sf::Sprite explosion;
	
	std::string bombTextureId = "graphics/spr_HoloBombThrow.png";
	std::string expSBId = "sound/snd_bigbombexplosion.wav";

	std::string explosionTextureId[13] =
	{
		"graphics/spr_bombExplode/spr_bombExplode_0.png",
		"graphics/spr_bombExplode/spr_bombExplode_1.png",
		"graphics/spr_bombExplode/spr_bombExplode_2.png",
		"graphics/spr_bombExplode/spr_bombExplode_3.png",
		"graphics/spr_bombExplode/spr_bombExplode_4.png",
		"graphics/spr_bombExplode/spr_bombExplode_5.png",
		"graphics/spr_bombExplode/spr_bombExplode_6.png",
		"graphics/spr_bombExplode/spr_bombExplode_7.png",
		"graphics/spr_bombExplode/spr_bombExplode_8.png",
		"graphics/spr_bombExplode/spr_bombExplode_9.png",
		"graphics/spr_bombExplode/spr_bombExplode_10.png",
		"graphics/spr_bombExplode/spr_bombExplode_11.png",
		"graphics/spr_bombExplode/spr_bombExplode_12.png",
	};

	SceneGame* sceneGame;

	std::list<Zombie*> dealtZombie;

	float expTimer;
	float expDelay;
	float expAnimationTimer;
	float expAnimationDelay;
	int   expIndex;
	bool isExplosion;

	sf::Vector2f direction;
	float speed;
	float initialSpeed;

public:
	Bomb(const std::string& name = "");
	~Bomb() = default;

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

	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float spd);
};
