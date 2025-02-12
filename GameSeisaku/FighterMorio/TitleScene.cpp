#include "TitleScene.h"
#include "SceneManager.h"
#include "StageSelectionScene.h"
#include "TitlePlayMovie.h"
#include "GameScene_1.h"

#include "game.h"

#include "DxLib.h"
#include "Pad.h"

TitleScene::TitleScene(SceneManager& manager) : 
	BaseScene(manager),
	m_pTitlePlayMovie(new TitlePlayMovie),
	m_Graph(0),
	m_TitleStart(0),
	m_BrinkCounter(0)
{
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_Graph);
	DeleteGraph(m_TitleStart);
	delete m_pTitlePlayMovie;
}

void TitleScene::Init()
{
	m_Graph = LoadGraph("data/image/FighterMorio.png");
	m_TitleStart = LoadGraph("data/image/TitleUIStart_A.png");
	if (m_pTitlePlayMovie != nullptr)
	{
		m_pTitlePlayMovie->Init();
	}
}

void TitleScene::Update()
{
	Pad::Update();
	// 入力状態を更新
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

#ifdef _DEBUG
	if (Pad::IsTrigger(input & PAD_INPUT_L))
	{
		m_pTitlePlayMovie->SetPlaySwitch(true);
		auto next = std::make_shared<StageSelectionScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
		return;
	}
#else	//_DEBUG
	if (Pad::IsTrigger(input & PAD_INPUT_A))
	{
		m_pTitlePlayMovie->SetPlaySwitch(true);
		auto next = std::make_shared<GameScene_1>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
		return;
	}
#endif  //_DEBUG

	if (m_pTitlePlayMovie != nullptr)
	{
		m_pTitlePlayMovie->Update();
	}

	// 点滅変数に1を足す
	m_BrinkCounter++;

	// 点滅変数が60になっていたら0にする
	if (m_BrinkCounter == 60)
	{
		m_BrinkCounter = 0;
	}
}

void TitleScene::Draw()
{
	DrawBox(0, 0, 1280, 640, 0x87cefa, true);
	if (m_pTitlePlayMovie != nullptr)
	{
		m_pTitlePlayMovie->Draw();
	}
	m_pTitlePlayMovie->Init();
#ifdef _DEBUG
	DrawBox(0, 0, 1280, 640, 0x999999, true);
	DrawFormatString(0, 0, 0xffffff, "TitleScene", true);
	DrawFormatString(550, 500, 0xffffff, "Aキーを押してください", true);
	DrawFormatString(550, 516, 0xffffff, "Yボタンを押してください", true);
	DrawRotaGraph(640, 200, 1.0, 0, m_Graph, TRUE);
#else	 //_DEBUG
	DrawRotaGraph(640, 200, 1.0, 0, m_Graph, TRUE);
#endif  //__DEBUG
	// 点滅用の変数の値が 30 未満のときだけ描画する
	if (m_BrinkCounter < 30)
	{
		DrawRotaGraph(640, 500, 0.5, 0, m_TitleStart, TRUE);
	}
}