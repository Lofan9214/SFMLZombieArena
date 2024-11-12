#include "stdafx.h"
#include "Animator.h"

void Animator::Update(float dt)
{
	if (!isPlaying)
	{
		return;
	}
	accumTime += dt;
	if (accumTime < frameDuration)
	{
		return;
	}

	++currentFrame;
	accumTime = 0.f;

	if (currentFrame == totalFrame)
	{
		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = totalFrame - 1;
			isPlaying = false;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = 0;
			break;
		default:
			break;
		}
	}

	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::Play(AnimationClip* clip,bool queueclear)
{
	if (currentClip == clip)
	{
		return;
	}

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
