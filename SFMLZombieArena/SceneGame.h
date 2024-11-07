#pragma once
#include "Scene.h"

class Player;
class Zombie;
class TileMap;
class Bullet;
class Blood;
class UiHud;
class ItemGenerator;
class UiUpgrade;
class UiGameMessage;
class Item;
class Bomb;
enum class ItemTypes;
enum class Upgrade;

class SceneGame :
    public Scene
{
public:
	enum class Status
	{
		Awake,
		InGame,
		GameOver,
		Upgrade,
		Pause,
	};

protected:
	Status currentStatus = Status::Awake;

	Player* player;
	TileMap* tilemap;
	UiHud* uiHud;
	UiUpgrade* uiUpgrade;
	UiGameMessage* uiGameMessage;
	ItemGenerator* itemGenerator;
	
	std::list<Zombie*> zombies;
	ObjectPool<Zombie> zombiePool;

	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;

	std::list<Item*> items;
	ObjectPool<Item> itemPool;

	std::list<Blood*> bloods;
	ObjectPool<Blood> bloodPool;

	std::list<Bomb*> bombs;
	ObjectPool<Bomb> bombPool;

	sf::Sprite cursor;

	int score;
	int highScore;
	int wutheringWave;
	int spawncount;
	float spawnTimer;

public:

    SceneGame();
    virtual ~SceneGame() = default;

    void Init() override;
    void Release() override;
    
    void Enter() override;
    void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetStatus(Status status);
	void UpdateAwake(float dt);
	void UpdateInGame(float dt);
	void UpdateUpgrade(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void UpdateHud();

    void SpawnZombies(int count);
    const std::list<Zombie*>& GetZombieList() const { return zombies; }
    Bullet* TakeBullet();
	Bomb* TakeBomb();

    void SpawnItem(Upgrade type, int qt);
    
	void OnItemTake(Item* item);
	
	void OnZombieDie(Zombie* zombie);
	void OnExplosionEnd(Bomb* bomb);
	void OnPlayerDie();

	void ReturnBullet(Bullet* bullet);
	void ReturnBlood(Blood* blood);
	
	void OnUpgrade(Upgrade up);
};

