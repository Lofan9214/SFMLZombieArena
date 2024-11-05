#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Zombie.h"
#include "TileMap.h"
#include "Bullet.h"
#include "ItemGenerator.h"
#include "Item.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	tilemap = AddGo(new TileMap("TileMap"));
	player = AddGo(new Player("Player"));
	AddGo(new ItemGenerator("ItemGenerator"));


	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	worldView.setSize(FRAMEWORK.GetWindowSizef());
	worldView.setCenter(0.f, 0.f);
	Scene::Enter();
}

void SceneGame::Exit()
{
	for (auto zombie : zombies)
	{
		RemoveGo(zombie);
		zombiePool.Return(zombie);
	}
	zombies.clear();

	for (auto bullet : bullets)
	{
		RemoveGo(bullet);
		bulletPool.Return(bullet);
	}
	bullets.clear();

	for (auto item : items)
	{
		RemoveGo(item);
		itemPool.Return(item);
	}
	items.clear();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombies(100);
	}

	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}
}

void SceneGame::SpawnZombies(int count)
{
	for (int i = 0;i < count;++i)
	{
		Zombie* zombie = zombiePool.Take();
		zombies.push_back(zombie);

		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes - 1);
		zombie->SetType(zombieType);

		sf::FloatRect bounds = tilemap->GetGlobalBounds();
		sf::Vector2f pos;
		pos.x = Utils::RandomRange(bounds.left, bounds.left + bounds.width);
		pos.y = Utils::RandomRange(bounds.top, bounds.top + bounds.height);
		zombie->SetPosition(pos);

		AddGo(zombie);
	}
}

Bullet* SceneGame::TakeBullet()
{
	Bullet* bullet = bulletPool.Take();
	bullets.push_back(bullet);
	AddGo(bullet);
	return bullet;
}

void SceneGame::SpawnItem()
{
	Item* item = itemPool.Take();
	items.push_back(item);
	Item::Types itemType = (Item::Types)Utils::RandomRange(0, Item::TotalTypes - 1);
	item->SetType(itemType);

	sf::FloatRect bounds = tilemap->GetMovableBounds();
	sf::Vector2f pos;
	pos.x = Utils::RandomRange(bounds.left, bounds.left + bounds.width);
	pos.y = Utils::RandomRange(bounds.top, bounds.top + bounds.height);
	item->SetPosition(pos);

	AddGo(item);
}

void SceneGame::OnItemTake(Item* item)
{
	RemoveGo(item);
	itemPool.Return(item);
	items.remove(item);
}

void SceneGame::OnZombieDie(Zombie* zombie)
{
	RemoveGo(zombie);
	zombiePool.Return(zombie);
	zombies.remove(zombie);
}

void SceneGame::ReturnBullet(Bullet* bullet)
{
	RemoveGo(bullet);
	bulletPool.Return(bullet);
	bullets.remove(bullet);
}
