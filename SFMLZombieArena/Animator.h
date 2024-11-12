#pragma once

#include "AnimationClip.h"

class Animator
{
protected:
	AnimationClip* currentClip;
	AnimationClip* idleClip;
	sf::Sprite* sprite;

	bool isPlaying = false;
	int currentFrame = 0;
	int totalFrame = 0;
	float frameDuration = 0.f;
	float accumTime = 0.f;

	std::list<AnimationClip*> clips;
	std::queue<AnimationClip*> queclip;

public:
	Animator() = default;
	virtual ~Animator() = default;

	void SetTarget(sf::Sprite* target) { sprite = target; }

	void Update(float dt);

	bool IsPlaying() const { return isPlaying; }

	void Play(AnimationClip* clip, bool queueclear = true);
	void Stop();
	//void Pause();

	void SetFrame(const AnimationFrame& frame);
};

