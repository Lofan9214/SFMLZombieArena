#include "stdafx.h"
#include "Animator.h"

void Animator::AddEvent(const std::string& id, int frame, const std::function<void()>& action)
{
	auto it = events.find({ id,frame });
	if (it != events.end() && action)
	{
		it->second.push_back(action);
		return;
	}
	events.insert({ { id,frame }, {action} });
}

void Animator::ClearEvent(const std::string& id, int frame)
{
	auto it = events.find({ id,frame });
	if (it != events.end())
	{
		it->second.clear();
		return;
	}
}

void Animator::Update(float dt)
{
	if (!isPlaying)
	{
		return;
	}
	accumTime += dt * std::fabs(speed);
	if (accumTime < frameDuration)
	{
		return;
	}

	currentFrame += speed > 0.f ? 1 : -1;

	if (currentFrame == checkFrame)
	{
		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = speed > 0.f ? totalFrame - 1 : 0;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = speed > 0.f ? 0 : totalFrame - 1;
			break;
		}
	}

	accumTime = 0.f;

	SetFrame(currentClip->frames[currentFrame]);

	auto find = events.find({ currentClip->id,currentFrame });
	if (find != events.end())
	{
		auto& evs = *find;
		for (auto& ev : evs.second)
		{
			ev();
		}
	}

}

void Animator::Play(const std::string& clipId)
{
	Play(&ANIMATIONCLIP_MGR.Get(clipId));
}

void Animator::Play(AnimationClip* clip)
{
	isPlaying = true;

	currentClip = clip;
	totalFrame = currentClip->frames.size();
	checkFrame = this->speed > 0.f ? totalFrame : -1;
	currentFrame = speed < 0 ? totalFrame - 1 : 0;

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
