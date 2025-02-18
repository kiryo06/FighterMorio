#pragma once
#include "BaseScene.h"
#include "GameClear.h"

class SceneManager;
class GameClear;
class GameClearScene : public BaseScene
{
public:
    GameClearScene(SceneManager& manager);
    virtual ~GameClearScene() override;
    void Init() override;
    void Update() override;
    void Draw() override;
private:
    GameClear* m_pGameClear;
};
