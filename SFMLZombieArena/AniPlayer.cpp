#include "stdafx.h"
#include "AniPlayer.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniPlayer::Init()
{
	animator.SetTarget(&body);
	std::string sheetId = "graphics/sprite_sheet.png";

	sf::IntRect coord(0, 0, 120, 120);

	//Idle
	idle.id = "Idle";
	idle.fps = 10;
	idle.loopType = AnimationLoopTypes::Loop;

	for (int i = 0;i < 8;++i)
	{
		coord.left = i * 120;
		idle.frames.push_back(AnimationFrame(sheetId, coord));
	}

	run.id = "Run";
	run.fps = 10;
	run.loopType = AnimationLoopTypes::Loop;

	for (int i = 0;i < 9;++i)
	{
		coord.left = (i % 8) * 120;
		coord.top = (1 + i / 8) * 120;

		run.frames.push_back(AnimationFrame(sheetId, coord));
	}

	jump.id = "Jump";
	jump.fps = 10;
	jump.loopType = AnimationLoopTypes::Single;

	for (int i = 0;i < 7;++i)
	{
		coord.left = (i % 8) * 120;
		coord.top = (3 + i / 8) * 120;

		jump.frames.push_back(AnimationFrame(sheetId, coord));
	}
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	animator.Play(&idle);
	SetOrigin(Origins::BC);
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);

	float h = 0.f;

	if (InputMgr::GetKeyDown(sf::Keyboard::Space) && isGrounded)
	{
		isGrounded = false;
		velocity.y = -500.f;
		animator.Play(&jump);
	}
	if (!isGrounded)
	{
		velocity += gravity * dt;
	}
	else
	{
		h = InputMgr::GetAxis(Axis::Horizontal);
		velocity.x = h * speed;
	}
	if (h != 0.f)
	{
		body.setScale({ h > 0 ? 1.f : -1.f,1.f });
	}

	position += velocity * dt;

	if (position.y > 0.f)
	{
		isGrounded = true;
		velocity.y = 0.f;
		position.y = 0.f;
	}

	SetPosition(position);

	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad1))
	{
		animator.SetSpeed(-0.5f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad4))
	{
		animator.SetSpeed(-1.f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad7))
	{
		animator.SetSpeed(-2.f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad3))
	{
		animator.SetSpeed(0.5f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad6))
	{
		animator.SetSpeed(1.f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad9))
	{
		animator.SetSpeed(2.f);
	}


	if (animator.GetCurrentClipId() == "Idle")
	{
		if (h != 0.f)
		{
			animator.Play(&run);
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (h == 0.f)
		{
			animator.Play(&idle);
		}
	}
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded)
	{
		if (h == 0.f)
		{
			animator.Play(&idle);
		}
		else
		{
			animator.Play(&run);
		}
	}
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
