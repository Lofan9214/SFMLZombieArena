#include "stdafx.h"
#include "SceneDev2.h"
#include "TextGo.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	auto text = AddGo(new TextGo("fonts/malgun.ttf", "SceneName 1"));
	auto text2 = AddGo(new TextGo("fonts/malgun.ttf", "SceneName 2"));

	text->sortingLayer = SortingLayers::UI;
	text->SetFillColor(sf::Color::White);
	text->SetCharSize(25);
	
	text->SetString("Hi");


	text2->sortingLayer = SortingLayers::UI;
	text2->SetPosition({ 0.f,100.f });
	text2->SetFillColor(sf::Color::White);
	text2->SetCharSize(25);
	
	text2->SetString("Hi");

	Scene::Init();
}

void SceneDev2::Enter()
{
	Scene::Enter();
}

void SceneDev2::Exit()
{
	Scene::Exit();

}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
