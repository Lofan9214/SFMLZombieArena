#pragma once
#include "Scene.h"

class TextGo;
class AniPlayer;


class SceneDev2 : public Scene
{
protected:

	AniPlayer* aniPlayer;

	TextGo* text;
	TextGo* text2;

public:
	SceneDev2();
	~SceneDev2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

