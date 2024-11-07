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
class UiGameOver;
class Item;
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
	UiGameOver* uiGameOver;
	ItemGenerator* itemGenerator;
	
	std::list<Zombie*> zombies;
	ObjectPool<Zombie> zombiePool;

	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;

	std::list<Item*> items;
	ObjectPool<Item> itemPool;

	std::list<Blood*> bloods;
	ObjectPool<Blood> bloodPool;

	sf::Sprite cursor;

	int score;
	int hiscore;
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

    void SpawnZombies(int count);
    Bullet* TakeBullet();
    void SpawnItem(ItemTypes type, int qt);
    void OnItemTake(Item* item);


    const std::list<Zombie*>& GetZombieList() const { return zombies; }

	void OnZombieDie(Zombie* zombie);
	void ReturnBullet(Bullet* bullet);
	void ReturnBlood(Blood* blood);
	
	void OnUpgrade(Upgrade up);
};

