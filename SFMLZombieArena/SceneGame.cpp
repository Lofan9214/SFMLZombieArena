#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "Zombie.h"
#include "TileMap.h"
#include "Bullet.h"
#include "ItemGenerator.h"
#include "Blood.h"
#include "Item.h"
#include "Bomb.h"
#include "UiHud.h"
#include "UiUpgrade.h"
#include "UiGameMessage.h"

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
	uiGameMessage = AddGo(new UiGameMessage("UiGameMessage"));
	SOUNDBUFFER_MGR.Load("sound/bgm_suspect.ogg", true);
	SOUND_MGR.PlayBgm("sound/bgm_suspect.ogg");
	SOUND_MGR.SetBgmVolume(20.f);
	SOUND_MGR.SetSfxVolume(20.f);

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
	uiGameMessage->SetActive(false);

	itemGenerator->SetActive(false);

	score = 0;
	wutheringWave = 0;
	SetStatus(Status::Awake);
	Scene::Enter();
	player->SetMovableBounds(tilemap->GetMovableBounds());
	player->SetBombIcon(uiHud->GetBombIcon());
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

	for (auto bomb : bombs)
	{
		RemoveGo(bomb);
		bombPool.Return(bomb);
	}
	bombs.clear();

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

	UpdateHud();
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

	uiGameMessage->SetActive(false);
	itemGenerator->SetActive(false);
	FRAMEWORK.SetTimeScale(0.f);


	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		uiGameMessage->SetActive(true);
		uiGameMessage->SetStat(false);

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
		uiGameMessage->SetActive(true);
		uiGameMessage->SetStat(true);
		break;
	case SceneGame::Status::Upgrade:
		uiUpgrade->SetActive(true);
		break;
	case SceneGame::Status::Pause:
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

	if (zombies.size() <= 0 && spawncount <= 0)
	{
		SetStatus(Status::Upgrade);
	}
}

void SceneGame::UpdateUpgrade(float dt)
{
}

void SceneGame::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}

void SceneGame::UpdatePause(float dt)
{
}

void SceneGame::UpdateHud()
{
	uiHud->SetAmmo(player->GetAmmo(), player->GetTotalAmmo());
	uiHud->SetHp(player->GetHp(), player->GetMaxHp());
	uiHud->SetWave(wutheringWave);
	uiHud->SetZombieCount(zombies.size());
	uiHud->SetScore(score);
	uiHud->SetHighScore(highScore);
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
		sf::Vector2f plpos = player->GetPosition();
		sf::FloatRect forbid = { {plpos.x - 300.f,plpos.y - 300.f},{600.f,600.f} };

		do
		{
			pos.x = Utils::RandomRange(bounds.left, bounds.left + bounds.width);
			pos.y = Utils::RandomRange(bounds.top, bounds.top + bounds.height);
		} while (forbid.contains(pos));

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

Bomb* SceneGame::TakeBomb()
{
	Bomb* bomb = bombPool.Take();
	bombs.push_back(bomb);
	AddGo(bomb);
	return bomb;
}

void SceneGame::SpawnItem(Upgrade type, int qt)
{
	Item* item = itemPool.Take();
	items.push_back(item);
	item->SetType(type, qt);

	sf::FloatRect bounds = tilemap->GetMovableBounds();
	sf::Vector2f pos;
	sf::Vector2f plpos = player->GetPosition();
	sf::FloatRect forbid = { {plpos.x - 300.f,plpos.y - 300.f},{600.f,600.f} };

	do
	{
		pos.x = Utils::RandomRange(bounds.left, bounds.left + bounds.width);
		pos.y = Utils::RandomRange(bounds.top, bounds.top + bounds.height);
	} while (forbid.contains(pos));
	item->SetPosition(pos);

	AddGo(item);
}

void SceneGame::OnItemTake(Item* item)
{
	SOUND_MGR.PlaySfx("sound/pickup.wav");
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

	score += 10;
	if (score > highScore)
	{
		highScore = score;
	}

	RemoveGo(zombie);
	zombiePool.Return(zombie);
	zombies.remove(zombie);
}

void SceneGame::OnPlayerDie()
{
	SetStatus(Status::GameOver);
}

void SceneGame::OnExplosionEnd(Bomb* bomb)
{
	RemoveGo(bomb);
	bombPool.Return(bomb);
	bombs.remove(bomb);
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
	SOUND_MGR.PlaySfx("sound/powerup.wav");
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

