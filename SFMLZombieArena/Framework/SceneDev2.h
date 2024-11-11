#pragma once
#include "Scene.h"

class TextGo;

class SceneDev2 : public Scene
{
protected:

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

