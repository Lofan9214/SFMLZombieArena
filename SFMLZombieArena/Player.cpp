#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "UiUpgrade.h"

Player::Player(const std::string& name)
	: GameObject(name), sceneGame(nullptr)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Player::SetMovableBounds(const sf::FloatRect& bounds)
{
	movableBounds = bounds;
	sf::FloatRect playerRect = GetLocalBounds();
	movableBounds.left += playerRect.width * 0.5f;
	movableBounds.width -= playerRect.width;
	movableBounds.top += playerRect.height * 0.5f;
	movableBounds.height -= playerRect.height;
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 3;
	SetOrigin(Origins::MC);
}

void Player::Release()
{
}

void Player::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(originPreset);
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);
	direction = { 0.f,0.f };

	hp = 100;
	maxHp = 100;
	ammo = 15;
	totalAmmo = 150;
	clip = 15;
	shootDelay = 0.5f;
	speed = 500.f;
}

void Player::LateUpdate(float dt)
{
}

void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)
	{
		Utils::Normalize(direction);
	}
	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = (sf::Vector2f)mousePos;

	if (sceneGame != nullptr)
	{
		mouseWorldPos = sceneGame->ScreenToWorld(mousePos);
	}

	look = Utils::GetNormal(mouseWorldPos - position);
	SetRotation(Utils::Angle(look));

	sf::Vector2f newpos = position + direction * speed * dt;
	if (newpos.y < movableBounds.top)
	{
		newpos.y = movableBounds.top;
	}
	else if (newpos.y > movableBounds.top + movableBounds.height)
	{
		newpos.y = movableBounds.top + movableBounds.height;
	}
	if (newpos.x < movableBounds.left)
	{
		newpos.x = movableBounds.left;
	}
	else if (newpos.x > movableBounds.left + movableBounds.width)
	{
		newpos.x = movableBounds.left + movableBounds.width;
	}
	SetPosition(newpos);

	shootTimer += dt;
	if (isReloading)
	{
		reloadTimer += dt;
		if (reloadTimer > reloadDelay)
		{
			if (totalAmmo < clip)
			{
				ammo = totalAmmo;
				totalAmmo = 0;
			}
			else
			{
				totalAmmo -= clip;
				ammo = clip;
			}
			isReloading = false;
		}
	}
	else if (ammo <= 0 || InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		Reload();
	}
	else if (InputMgr::GetMouseButtonPressing(sf::Mouse::Left) && shootTimer > shootDelay)
	{
		--ammo;
		shootTimer = 0.f;
		Shoot();
	}


	if (isDamaged)
	{
		damageTimer += dt;
		if (damageTimer > damageDelay)
		{
			isDamaged = false;
			body.setColor(sf::Color::White);
		}
	}

	hitBox.UpdateTr(body, body.getLocalBounds());

	debugBox.SetBounds(GetGlobalBounds());
	debugBox.SetOutlineColor(sf::Color::Green);
}

void Player::FixedUpdate(float dt)
{
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	debugBox.Draw(window);
}

void Player::Shoot()
{
	Bullet* bullet = sceneGame->TakeBullet();
	bullet->Fire(position, look, 800.f, 10);
}

void Player::Reload()
{
	if (!isReloading)
	{
		isReloading = true;
		reloadTimer = 0.f;
		totalAmmo += ammo;
		ammo = 0;
	}
}

void Player::OnHealth(int hp)
{
	debugBox.SetOutlineColor(sf::Color::Blue);
	this->hp = Utils::Clamp(this->hp + hp, 0, maxHp);
}

void Player::OnAmmo(int ammo)
{
	debugBox.SetOutlineColor(sf::Color::Yellow);
	this->totalAmmo += ammo;
}

void Player::OnDamage(int d)
{
	if (!isDamaged)
	{
		isDamaged = true;
		damageTimer = 0.f;
		hp = Utils::Clamp(hp - d, 0, maxHp);
		debugBox.SetOutlineColor(sf::Color::Red);
		body.setColor(sf::Color(127, 127, 127, 255));
	}

	if (hp > 0)
	{
		return;
	}
}

void Player::UpgradeStat(Upgrade upgrade)
{
	switch (upgrade)
	{
	case Upgrade::RateOfFire:
		shootDelay *= 0.9;
		break;
	case Upgrade::ClipSize:
		clip += 5;
		break;
	case Upgrade::MaxHealth:
		maxHp += 50;
		hp += 50;
		break;
	case Upgrade::RunSpeed:
		speed += 100.f;
		break;
	}
}