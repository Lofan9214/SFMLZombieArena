#pragma once
#include "Scene.h"

class Player;
class Zombie;
class TileMap;
class Bullet;
class Item;
class UiHud;
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
	
	std::list<Zombie*> zombies;
	ObjectPool<Zombie> zombiePool;

	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;

	std::list<Item*> items;
	ObjectPool<Item> itemPool;

	sf::Sprite cursor;

	int score;
	int hiscore;

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
    void SpawnItem();
    void OnItemTake(Item* item);


    const std::list<Zombie*>& GetZombieList() const { return zombies; }

	void OnZombieDie(Zombie* zombie);
	void ReturnBullet(Bullet* bullet);

	void OnUpgrade(int up);
};

