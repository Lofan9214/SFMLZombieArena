#include "stdafx.h"
#include "SceneDev2.h"
#include "TextGo.h"
#include "AniPlayer.h"
#include "AniPlayer2.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	aniPlayer = AddGo(new AniPlayer("Ani Test"));
	aniPlayer2 = AddGo(new AniPlayer2("Ani Test"));
	Scene::Init();

	std::ifstream f("json/example.json");
	json data = json::parse(f);
	std::cout << data["pi"] << std::endl;
	std::cout << data["happy"] << std::endl;
	
}

void SceneDev2::Enter()
{
	Scene::Enter();

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(FRAMEWORK.GetWindowSizef());
}

void SceneDev2::Exit()
{
	Scene::Exit();

}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);


	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		Variables::currentLang = Languages::Korean;
		OnLocalize(Variables::currentLang);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		Variables::currentLang = Languages::English;
		OnLocalize(Variables::currentLang);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		Variables::currentLang = Languages::Japanese;
		OnLocalize(Variables::currentLang);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
