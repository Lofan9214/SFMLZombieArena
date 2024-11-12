#pragma once

#include "AnimationClip.h"

class Animator
{
protected:
	AnimationClip* currentClip;
	sf::Sprite* sprite;

	bool isPlaying = false;
	int currentFrame = 0;
	int totalFrame = 0;
	int checkFrame = 0;
	float frameDuration = 0.f;
	float accumTime = 0.f;

	float speed = 1.f;

public:
	Animator() = default;
	virtual ~Animator() = default;

	void SetSpeed(float speed)
	{
		this->speed = speed;
		checkFrame = this->speed > 0.f ? totalFrame : -1;
	}

	void SetTarget(sf::Sprite* target) { sprite = target; }

	void Update(float dt);

	bool IsPlaying() const { return isPlaying; }

	void Play(AnimationClip* clip);
	void Stop();
	//void Pause();

	void SetFrame(const AnimationFrame& frame);

	const std::string& GetCurrentClipId()
	{
		if (currentClip == nullptr)
		{
			return "";
		}
		return currentClip->id;
	}
};

