#pragma once
#include "Scene.h"

class Player;

class SceneGame :
    public Scene
{
protected:
    Player* player;

public:

    SceneGame();
    virtual ~SceneGame() = default;

    void Init() override;
    void Release() override;
    
    void Enter() override;
    void Exit() override;

    void Update(float dt) override;
};

