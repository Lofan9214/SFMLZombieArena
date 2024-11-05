#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "TileMap.h"

Player::Player(const std::string& name)
	: GameObject(name)
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

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
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
	movableBounds = dynamic_cast<TileMap*>(sceneGame->FindGo("TileMap"))->GetMovableBounds();
	sf::FloatRect playerRect = GetLocalBounds();
	movableBounds.left += playerRect.width * 0.5f;
	movableBounds.width -= playerRect.width;
	movableBounds.top += playerRect.height * 0.5f;
	movableBounds.height -= playerRect.height;
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
	if (shootTimer > shootDelay && InputMgr::GetMouseButtonPressing(sf::Mouse::Left))
	{
		shootTimer = 0.f;
		Shoot();
	}

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

void Player::OnHealth(int hp)
{
	this->hp += hp;
}

void Player::OnAmmo(int ammo)
{
	this->ammo += ammo;
}

void Player::OnDamage(int d)
{
	debugBox.SetOutlineColor(sf::Color::Red);
}