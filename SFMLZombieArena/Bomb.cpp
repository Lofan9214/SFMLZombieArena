#include "stdafx.h"
#include "Bomb.h"
#include "SceneGame.h"
#include "Zombie.h"

Bomb::Bomb(const std::string& name)
	: GameObject(name)
{
}

void Bomb::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	bomb.setPosition(position);
	explosion.setPosition(position);
}

void Bomb::SetRotation(float angle)
{
	rotation = angle;
}

void Bomb::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Bomb::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(bomb, originPreset);
		Utils::SetOrigin(explosion, originPreset);
	}
}

void Bomb::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	bomb.setOrigin(origin);
}

void Bomb::Init()
{
}

void Bomb::Release()
{
}

void Bomb::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	bomb.setTexture(TEXTURE_MGR.Get(bombTextureId));
	explosion.setTexture(TEXTURE_MGR.Get(explosionTextureId[0]));

	SetOrigin(Origins::MC);

	expTimer = 0.f;
	expDelay = 1.f;
	expAnimationTimer = 0.f;
	expAnimationDelay = 0.05f;
	expIndex = 0;
	isExplosion = false;
	dealtZombie.clear();
}

void Bomb::LateUpdate(float dt)
{
}

void Bomb::Update(float dt)
{
	if (!isExplosion)
	{
		expTimer += dt;
		float newspeed = Utils::Lerp(speed, 0, expTimer * 2.f);

		SetPosition(position + direction * newspeed * dt);
		hitBox.UpdateTr(explosion, explosion.getLocalBounds());

		if (expTimer > expDelay)
		{
			SOUND_MGR.PlaySfx(expSBId);

			isExplosion = true;
		}
		return;
	}

	expAnimationTimer += dt;
	if (expAnimationTimer > expAnimationDelay)
	{
		expAnimationTimer = 0.f;
		++expIndex;
	}

	if (expIndex == 13)
	{
		if (sceneGame != nullptr)
		{
			sceneGame->OnExplosionEnd(this);
		}
		return;
	}

	explosion.setTexture(TEXTURE_MGR.Get(explosionTextureId[expIndex]));
}

void Bomb::FixedUpdate(float dt)
{
	if (!isExplosion || sceneGame == nullptr)
	{
		return;
	}
	auto zombies = sceneGame->GetZombieList();

	for (auto zombie : zombies)
	{
		if (find(dealtZombie.begin(), dealtZombie.end(), zombie) == dealtZombie.end()
			&& explosion.getGlobalBounds().intersects(zombie->GetGlobalBounds())
			&& Utils::CheckCollision(hitBox, zombie->GetHitBox()))
		{
			dealtZombie.push_back(zombie);
			zombie->OnDamage(50);
		}
	}
}

void Bomb::Draw(sf::RenderWindow& window)
{
	if (isExplosion)
	{
		window.draw(explosion);
	}
	else
	{
		window.draw(bomb);
	}
}

void Bomb::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float spd)
{
	SetPosition(pos);
	direction = dir;
	speed = spd;
}
