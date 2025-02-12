#include "StageSelectionScene.h"
#include "SceneManager.h"
#include "GameScene.h"

#include "DxLib.h"
#include "Pad.h"

StageSelectionScene::StageSelectionScene(SceneManager& manager) : BaseScene(manager)
{
}

StageSelectionScene::~StageSelectionScene()
{
}

void StageSelectionScene::Init()
{
}

void StageSelectionScene::Update()
{
	Pad::Update();
	// “ü—Íó‘Ô‚ğXV
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Pad::IsTrigger(input & PAD_INPUT_L))
	{
		auto next = std::make_shared<GameScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
		return;
	}
}

void StageSelectionScene::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "StageSelectionScene", true);
	DrawBox(100, 100, 640, 640, 0xaa00aa, true);
}
