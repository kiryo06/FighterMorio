#pragma once
#include <memory>
#include"BaseScene.h"

enum class SceneState
{
	Title,
	StageSelecion,
	Game,
	Game_1,
	Game_2,
	GameOver,
	GameClear
};

class SceneManager
{
public:

	// インストラクタ
	SceneManager();
	// デストラクタ
	~SceneManager();
	void Init();
	void Update();
	void Draw();
	void ChangeScene(const std::shared_ptr<BaseScene>& next);
private:
	
	// void ChangeScene(SceneState nextSceneState);
	std::shared_ptr<BaseScene>m_pScene;

	SceneState m_sceneState;
};