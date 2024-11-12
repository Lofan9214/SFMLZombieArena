#include "stdafx.h"
#include "Animator.h"

void Animator::Update(float dt)
{
	if (!isPlaying)
	{
		return;
	}
	accumTime += dt * frameScale;
	if (accumTime < frameDuration && accumTime > frameDuration * -1.f)
	{
		return;
	}
	if (accumTime > 0)
	{
		++currentFrame;
		if (currentFrame == totalFrame)
		{
			switch (currentClip->loopType)
			{
			case AnimationLoopTypes::Single:
				currentFrame = totalFrame - 1;
				break;
			case AnimationLoopTypes::Loop:
				currentFrame = 0;
				break;
			}
		}
	}
	else
	{
		--currentFrame;
		if (currentFrame == -1)
		{
			switch (currentClip->loopType)
			{
			case AnimationLoopTypes::Single:
				currentFrame = 0;
				break;
			case AnimationLoopTypes::Loop:
				currentFrame = totalFrame - 1;
				break;
			}
		}
	}
	accumTime = 0.f;

	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::Play(AnimationClip* clip)
{
	isPlaying = true;

	currentClip = clip;
	currentFrame = 0;
	totalFrame = currentClip->frames.size();

	frameDuration = 1.f / currentClip->fps;

	accumTime = 0.f;

	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::Stop()
{
	isPlaying = false;
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	sprite->setTexture(TEXTURE_MGR.Get(frame.texId));
	sprite->setTextureRect(frame.texCoord);
}

//void Animator::Pause()
//{
//}
