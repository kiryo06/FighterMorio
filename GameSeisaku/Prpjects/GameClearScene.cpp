#include "GameClearScene.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene_1.h"
#ifdef _DEBUG
#include "GameOverScene.h"
#endif // _DEBUG

#include "DxLib.h"
#include "Pad.h"
#include "Debug.h"

#include "GameClear.h"


GameClearScene::GameClearScene(SceneManager& manager) : BaseScene(manager),
m_pGameClear(new GameClear())
{
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::Init()
{
	m_pGameClear->Init();
}

void GameClearScene::Update()
{
	Pad::Update();
	// 入力状態を更新
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_pGameClear->Update();

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
	if (Pad::IsTrigger(input & PAD_INPUT_L))
	{
		auto next = std::make_shared<GameOverScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
#endif // _DEBUG
}

void GameClearScene::Draw()
{
	m_pGameClear->Draw();
}
