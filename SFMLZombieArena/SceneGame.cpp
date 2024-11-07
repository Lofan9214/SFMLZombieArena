#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Zombie.h"
#include "TileMap.h"
#include "Bullet.h"
#include "ItemGenerator.h"
#include "Blood.h"
#include "Item.h"
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

	itemGenerator->SetActive(false);

	score = 0;
	wutheringWave = 0;

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

	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}

	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneGame::Status::InGame:
		UpdateInGame(dt);
		break;
	case SceneGame::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneGame::Status::Upgrade:
		UpdateUpgrade(dt);
		break;
	case SceneGame::Status::Pause:
		UpdatePause(dt);
		break;
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

void SceneGame::SetStatus(Status status)
{
	Status prev = currentStatus;
	currentStatus = status;

	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case SceneGame::Status::InGame:
		FRAMEWORK.SetTimeScale(1.f);
		uiUpgrade->SetActive(false);
		itemGenerator->SetActive(true);
		++wutheringWave;
		spawnTimer = 7.f;
		spawncount = wutheringWave * 10;
		break;
	case SceneGame::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		itemGenerator->SetActive(false);
		uiGameOver->SetActive(true);
		break;
	case SceneGame::Status::Upgrade:
		itemGenerator->SetActive(false);
		uiUpgrade->SetActive(true);
		break;
	case SceneGame::Status::Pause:
		itemGenerator->SetActive(false);
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}

void SceneGame::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::InGame);
	}
	uiHud->SetAmmo(player->GetAmmo(), player->GetTotalAmmo());
	uiHud->SetWave(wutheringWave);
}

void SceneGame::UpdateInGame(float dt)
{
	spawnTimer += dt;
	if (spawnTimer > 10.f)
	{
		spawnTimer = 0.f;
		if (spawncount > 0)
		{
			spawncount -= 10;
			SpawnZombies(10);
		}
	}
	int remainZombie = zombies.size();
	uiHud->SetAmmo(player->GetAmmo(), player->GetTotalAmmo());
	uiHud->SetHp(player->GetHp(), player->GetMaxHp());
	uiHud->SetWave(wutheringWave);
	uiHud->SetZombieCount(remainZombie);

	if (remainZombie <= 0 && spawncount <= 0)
	{
		SetStatus(Status::Upgrade);
	}
}

void SceneGame::UpdateUpgrade(float dt)
{
}

void SceneGame::UpdateGameOver(float dt)
{

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}

void SceneGame::UpdatePause(float dt)
{
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

void SceneGame::SpawnItem(ItemTypes type, int qt)
{
	Item* item = itemPool.Take();
	items.push_back(item);
	ItemTypes itemType = (ItemTypes)Utils::RandomRange(0, Item::TotalTypes - 1);
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

void SceneGame::OnUpgrade(Upgrade up)
{
	switch (up)
	{
	case Upgrade::RateOfFire:
	case Upgrade::ClipSize:
	case Upgrade::MaxHealth:
	case Upgrade::RunSpeed:
		player->UpgradeStat(up);
		break;
	case Upgrade::HealthPickups:
	case Upgrade::AmmoPickups:
		itemGenerator->UpgradeItem(up);
		break;
	}
	SetStatus(Status::InGame);
}

