#pragma once
#include "Scene.h"
#include "Item.h"

class Player;
class Zombie;
class TileMap;
class Bullet;
class Blood;
class UiHud;
class ItemGenerator;
class UiUpgrade;
class UiGameOver;

class SceneGame :
    public Scene
{
protected:
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
	int stage;

public:

    SceneGame();
    virtual ~SceneGame() = default;

    void Init() override;
    void Release() override;
    
    void Enter() override;
    void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

    void SpawnZombies(int count);
    Bullet* TakeBullet();
    void SpawnItem(Item::Types type, int qt);
    void OnItemTake(Item* item);


    const std::list<Zombie*>& GetZombieList() const { return zombies; }

	void OnZombieDie(Zombie* zombie);
	void ReturnBullet(Bullet* bullet);
	void ReturnBlood(Blood* blood);

	void OnUpgrade(int up);
};

