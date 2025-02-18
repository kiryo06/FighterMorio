#include "GameOverScene.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene_1.h"

#include "DxLib.h"
#include "Pad.h"
#include "Debug.h"

#include "GameOver.h"
#include "SceneChange.h"


GameOverScene::GameOverScene(SceneManager& manager) : BaseScene(manager),
m_pGameOver(new GameOver())
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init()
{
	m_pGameOver->Init();
}

void GameOverScene::Update()
{
	Pad::Update();
	// 入力状態を更新
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_pGameOver->Update();

	// もう一度
	if (Pad::IsTrigger(input & PAD_INPUT_A))
	{
		auto next = std::make_shared<GameScene_1>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}

	// タイトル画面に戻る
	if (Pad::IsTrigger(input & PAD_INPUT_B))
	{
		auto next = std::make_shared<TitleScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
#ifdef _DEBUG
	// タイトル画面に戻る
	if (Pad::IsTrigger(input & PAD_INPUT_L))
	{
		auto next = std::make_shared<TitleScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
#endif // _DEBUG

}

void GameOverScene::Draw()
{
	m_pGameOver->Draw();
}
