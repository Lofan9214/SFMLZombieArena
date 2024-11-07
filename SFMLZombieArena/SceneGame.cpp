#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Zombie.h"
#include "TileMap.h"
#include "Bullet.h"
#include "ItemGenerator.h"
#include "Blood.h"
#include "UiHud.h"
#include "UiUpgrade.h"
#include "UiGameOver.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	tilemap = AddGo(new TileMap("TileMap"));
	player = AddGo(new Player("Player"));
	itemGenerator = AddGo(new ItemGenerator("ItemGenerator"));
	uiHud = AddGo(new UiHud("UiHud"));
	uiUpgrade = AddGo(new UiUpgrade("UiUpgrade"));
	uiGameOver = AddGo(new UiGameOver("UiGameOver"));


	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);

	sf::Vector2f size = FRAMEWORK.GetWindowSizef();

	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	uiUpgrade->SetActive(false);
	uiGameOver->SetActive(false);

	score = 0;

	Scene::Enter();
	player->SetMovableBounds(tilemap->GetMovableBounds());
}

void SceneGame::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
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

	for (auto blood : bloods)
	{
		RemoveGo(blood);
		bloodPool.Return(blood);
	}
	bloods.clear();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	sf::Vector2f mousePos = ScreenToUi(InputMgr::GetMousePosition());
	cursor.setPosition(mousePos);

	Scene::Update(dt);

	uiHud->SetAmmo(player->GetAmmo(), player->GetTotalAmmo());
	uiHud->SetHp(player->GetHp(), player->GetMaxHp());

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombies(100);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F6))
	{
		uiUpgrade->SetActive(!uiUpgrade->IsActive());
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F7))
	{
		uiGameOver->SetActive(!uiGameOver->IsActive());
	}

	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	const sf::View& previousView = window.getView();
	window.setView(uiView);
	window.draw(cursor);
	window.setView(previousView);
}

void SceneGame::SpawnZombies(int count)
{
	for (int i = 0;i < count;++i)
	{
		Zombie* zombie = zombiePool.Take();
		zombies.push_back(zombie);
		zombie->SetMovableBounds(tilemap->GetMovableBounds());
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

void SceneGame::SpawnItem(Item::Types type, int qt)
{
	Item* item = itemPool.Take();
	items.push_back(item);
	Item::Types itemType = (Item::Types)Utils::RandomRange(0, Item::TotalTypes - 1);
	item->SetType(itemType, qt);

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
	Blood* blood;
	if (bloods.size() > 10)
	{
		blood = bloods.front();
		ReturnBlood(blood);
	}

	blood = bloodPool.Take();
	bloods.push_back(blood);
	AddGo(blood);
	blood->SetPosition(zombie->GetPosition());

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

void SceneGame::ReturnBlood(Blood* blood)
{
	RemoveGo(blood);
	bloodPool.Return(blood);
	bloods.remove(blood);
}

void SceneGame::OnUpgrade(int up)
{
	std::cout << up << std::endl;
}
