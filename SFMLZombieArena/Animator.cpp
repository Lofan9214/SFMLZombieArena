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
		if (!playQueue.empty())
		{
			std::string clipid = playQueue.front();
			Play(clipid, false);
			playQueue.pop();
			return;
		}

		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = std::abs(checkFrame) - 1;
			//currentFrame = speed > 0.f ? totalFrame - 1 : 0;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = totalFrame - std::abs(checkFrame);
			//currentFrame = speed > 0.f ? 0 : totalFrame - 1;
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

void Animator::Play(const std::string& clipId, bool clearqueue)
{
	Play(&ANIMATIONCLIP_MGR.Get(clipId), clearqueue);
}

void Animator::Play(AnimationClip* clip, bool clearqueue)
{
	if (clearqueue)
	{
		while (!playQueue.empty())
		{
			playQueue.pop();
		}
	}

	isPlaying = true;

	currentClip = clip;
	totalFrame = currentClip->frames.size();
	checkFrame = this->speed > 0.f ? totalFrame : -1;
	currentFrame = speed < 0 ? totalFrame - 1 : 0;

	frameDuration = 1.f / currentClip->fps;

	accumTime = 0.f;

	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::PlayQueue(const std::string& clipId)
{
	playQueue.push(clipId);
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
