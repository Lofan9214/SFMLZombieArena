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


	if (InputMgr::GetKeyPressing(sf::Keyboard::Space)&&animator.IsPlaying())
	{
		animator.Play(&jump);
	}
	else
 	{
		if (InputMgr::GetAxis(Axis::Horizontal) != 0.f)
		{
			body.setScale({ InputMgr::GetAxis(Axis::Horizontal) < 0 ? -1.f : 1.f,1.f });
			animator.Play(&run);
		}
		else
		{
			animator.Play(&idle);
		}
	}

}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
