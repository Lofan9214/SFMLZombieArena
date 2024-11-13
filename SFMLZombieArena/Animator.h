#pragma once

#include "AnimationClip.h"

struct AnimationEvent
{
	std::string id;
	int frame = 0;
	//std::vector<std::function<void()>> actions;

	bool operator==(const AnimationEvent& other) const { return (id == other.id) && (frame == other.frame); }
};

struct AnimationEventHash
{
	std::size_t operator()(const AnimationEvent& ev) const
	{
		std::hash<std::string> stringhash = std::hash<std::string>();
		std::size_t h1 = stringhash(ev.id);
		std::size_t h2 = std::hash<int>()(ev.frame);
		return h1 ^ (h2 << 1);
	}
};

class Animator
{
protected:
	std::unordered_map<AnimationEvent, std::vector<std::function<void()>>, AnimationEventHash> events;

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

	void AddEvent(const std::string& id, int frame, const std::function<void()>& action);
	void ClearEvent() { events.clear(); }
	void ClearEvent(const std::string& id, int frame);

	void Update(float dt);

	bool IsPlaying() const { return isPlaying; }

	void Play(const std::string& clipId);
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

