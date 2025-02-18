#include "GameScene_1.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene_2.h"
#include "GameOverScene.h"
#include "GameClearScene.h"

#include "DxLib.h"
#include "Pad.h"
#include "Debug.h"

#include "Screen.h"
#include "Camera.h"
#include "Map.h"
#include "MapData.h"
#include "Player.h"
#include "Kuribou.h"
#include "SystemEngineer.h"
#include "SceneChange.h"

namespace
{
	int PoozuSize = 20;
}

GameScene_1::GameScene_1(SceneManager& manager) : BaseScene(manager),
m_pMap(new Map()),
m_pCamera(new Camera()),
m_pPlayer(new Player()),
m_pKuribou(),
m_pSystemEngineer(new SystemEngineer),
m_pSceneChange(new SceneChange),
PlayerPosX(0.0f),
enemyNum(0),
m_FrameCounter(0),
m_Timer(0),
m_Poozu(false),
SetMenyu(false),
PlayerDeath(false),
m_kuribou00(true),
m_kuribou01(true),
m_kuribou02(true),
m_kuribou03(true),
m_kuribou04(true),
m_kuribou05(true),
m_kuribou06(true),
m_kuribou07(true),
m_kuribou08(true),
m_kuribou09(true),
m_kuribou10(true),
m_kuribou11(true),
m_kuribou12(true),
m_kuribou13(true),
m_kuribou14(true),
m_kuribou15(true),
m_kuribou16(true)
{
}

GameScene_1::~GameScene_1()
{
	delete m_pMap;
	delete m_pCamera;
	delete m_pSceneChange;
}

void GameScene_1::Init()
{
	m_pMap->Init(1);
	m_pCamera->Init();
	m_pPlayer->Init(1, m_pSystemEngineer);
	for (auto& item : m_pKuribou)
	{
		item->Init(1);
	}
	m_pSystemEngineer->Init();
}

void GameScene_1::Update()
{
	// 入力状態を更新
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Pad::Update();
	m_pPlayer->Update(m_pCamera, m_pKuribou, 1);
	for (auto& item : m_pKuribou)
	{
		item->Update(1, m_pPlayer);
	}
	m_pCamera->Update(m_pPlayer);
	m_pSystemEngineer->Update();
	m_pSceneChange->Update();
	SpawnPos();

	// ゲームクリア
	if (m_pPlayer->GetClear())
	{
		m_pSystemEngineer->SetBGM(true);
		m_pSystemEngineer->SetStop(true);
		m_pSystemEngineer->Update();
		m_FrameCounter++;
		if (m_FrameCounter >= 60 * 5)
		{
			m_pSceneChange->SetClear(true);
			if (m_pSceneChange->GetChange())
			{
				auto next = std::make_shared<GameClearScene>(m_sceneManager);
				m_sceneManager.ChangeScene(next);
				return;
			}
		}
	}

	// ゲームオーバー
	if (m_pPlayer->GetDeath())
	{
		m_pSystemEngineer->SetBGM(true);
		m_pSystemEngineer->SetStop(true);
		m_pSystemEngineer->Update();
		m_FrameCounter++;
		if (m_FrameCounter >= 60 * 3)
		{
			m_pSceneChange->SetDeath(true);
			if (m_pSceneChange->GetChange())
			{
				auto next = std::make_shared<GameOverScene>(m_sceneManager);
				m_sceneManager.ChangeScene(next);
				return;
			}
		}
	}
	if (SetMenyu)
	{
		if (Pad::IsTrigger(input & PAD_INPUT_B))
		{
			m_pSystemEngineer->SetBGM(true);
			m_pSystemEngineer->Update();
			auto next = std::make_shared<TitleScene>(m_sceneManager);
			m_sceneManager.ChangeScene(next);
			return;
		}
	}
	// 一時停止画面を写す
	if (!m_pPlayer->GetClear() && !m_pPlayer->GetDeath())
	{
		if (!SetMenyu && Pad::IsTrigger(input & PAD_INPUT_R))
		{
			m_pPlayer->SetStop(true);
			for (auto& item : m_pKuribou)
			{
				item->SetStop(true);
			}
			m_pSystemEngineer->SetBGM(true);
			m_pSystemEngineer->SetStop(true);
			m_Poozu = true;
			m_pSystemEngineer->Update();
			SetMenyu = true;
			return;
		}
		if (SetMenyu && Pad::IsTrigger(input & PAD_INPUT_R))
		{
			m_pPlayer->SetStop(false);
			for (auto& item : m_pKuribou)
			{
				item->SetStop(false);
			}
			m_pSystemEngineer->SetBGM(false);
			m_pSystemEngineer->SetStop(false);
			m_Poozu = false;
			m_pSystemEngineer->Init();
			SetMenyu = false;
			return;
		}
	}
	// シーン遷移
#ifdef _DEBUG
	if(Pad::IsTrigger(input & PAD_INPUT_L))
	{
		m_pSystemEngineer->SetBGM(true);
		m_pSystemEngineer->Update();
		auto next = std::make_shared<GameScene_2>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
		return;
	}
#endif  //_DEBUG
}

void GameScene_1::Draw()
{
	m_pMap->Draw(1, m_pCamera);
	m_pPlayer->Draw(1,m_pCamera);
	for (auto& item : m_pKuribou)
	{
		item->Draw(m_pCamera);
	}
	m_pSystemEngineer->Draw();
	if (m_Poozu)
	{
		DEBUG_TRANSPARENCY
			DrawBox(PoozuSize, PoozuSize, Game::kScreenWidth - PoozuSize, Game::kScreenHeight - PoozuSize, 0x444444, true);
		// ブレンドモードをリセット
		DEBUG_RESET
	}
#ifdef _DEBUG
	// 半透明の設定
	DEBUG_TRANSPARENCY
	DrawBox(0, 0, 300, 200, 0x444444, true);
	// ブレンドモードをリセット
	DEBUG_RESET
	DrawFormatString(0,   0 ,0xffffff, " GameScene_1         ", true);
	DrawFormatString(0,  16, 0xcc0000, " PlayerPosX    : %.1f", m_pPlayer->GetPlayerPos().x, true);
	DrawFormatString(0,  32, 0xcc0000, " PlayerPosY    : %.1f", m_pPlayer->GetPlayerPos().y, true);
	//DrawFormatString(0,  48, 0x00cc00, " KuribouPosX   : %.1f", newKuribou->GetKuribouPos().x, true);
	//DrawFormatString(0,  64, 0x00cc00, " KuribouPosY   : %.1f", newKuribou->GetKuribouPos().y, true);
	DrawFormatString(0,  80, 0xaaaaaa, " Kuribou       : %d  ", m_pKuribou.size(), true);
	DrawFormatString(0,  96, 0xaaaaaa, " PlayerDeath   : %1d ", m_pPlayer->GetPlayerDeath(), true);
	DrawFormatString(0, 112, 0xaaaaaa, " Score         : %1d ", m_pSystemEngineer->GetScore(), true);
	DrawFormatString(0, 128, 0xaaaaaa, "               : %1d ", 123456789, true);
	DrawFormatString(0, 144, 0xaaaaaa, "               : %.1f", 123456789, true);
	DrawFormatString(0, 160, 0x00aaaa, " CameraPosX    : %.1f", m_pCamera->GetCameraDrawOffset().x, true);
	DrawFormatString(0, 176, 0x00aaaa, " CameraPosY    : %.1f", m_pCamera->GetCameraDrawOffset().y, true);
#endif // _DEBUG
	m_pSceneChange->Draw();
}


















void GameScene_1::SpawnPos()
{
	PlayerPosX = m_pPlayer->GetPlayerPos().x;

	// 1体目
	if (m_kuribou01 && PlayerPosX >= Master::kSpawnPosX01)
	{
		EnemyPos(1);
	}
	// 2体目
	if (m_kuribou02 && PlayerPosX >= Master::kSpawnPosX02)
	{
		EnemyPos(2);
	}
	// 3体目
	if (m_kuribou03 && PlayerPosX >= Master::kSpawnPosX03)
	{
		EnemyPos(3);
	}
	// 4体目
	if (m_kuribou04 && PlayerPosX >= Master::kSpawnPosX04)
	{
		EnemyPos(4);
	}
	// 5体目
	if (m_kuribou05 && PlayerPosX >= Master::kSpawnPosX05)
	{
		EnemyPos(5);
	}
	// 6体目
	if (m_kuribou06 && PlayerPosX >= Master::kSpawnPosX06)
	{
		EnemyPos(6);
	}
	// 7体目
	if (m_kuribou07 && PlayerPosX >= Master::kSpawnPosX07)
	{
		EnemyPos(7);
	}
	// 8体目
	if (m_kuribou08 && PlayerPosX >= Master::kSpawnPosX08)
	{
		EnemyPos(8);
	}
	// 9体目
	if (m_kuribou09 && PlayerPosX >= Master::kSpawnPosX09)
	{
		EnemyPos(9);
	}
	// 10体目
	if (m_kuribou10 && PlayerPosX >= Master::kSpawnPosX10)
	{
		EnemyPos(10);
	}
	// 11体目
	if (m_kuribou11 && PlayerPosX >= Master::kSpawnPosX11)
	{
		EnemyPos(11);
	}
	// 12体目
	if (m_kuribou12 && PlayerPosX >= Master::kSpawnPosX12)
	{
		EnemyPos(12);
	}
	// 13体目
	if (m_kuribou13 && PlayerPosX >= Master::kSpawnPosX13)
	{
		EnemyPos(13);
	}
	// 14体目
	if (m_kuribou14 && PlayerPosX >= Master::kSpawnPosX14)
	{
		EnemyPos(14);
	}
	// 15体目
	if (m_kuribou15 && PlayerPosX >= Master::kSpawnPosX15)
	{
		EnemyPos(15);
	}
	// 15体目
	if (m_kuribou16 && PlayerPosX >= Master::kSpawnPosX16)
	{
		EnemyPos(16);
	}
}

void GameScene_1::EnemyPos(int EnemyNumber)
{
	// 敵1体目のスポーン位置
	if (EnemyNumber == 1)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX01);
		newKuribou->SetPosY(Master::kKuribouPosY01);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou01 = false;
	}
	// 敵2体目のスポーン位置
	if (EnemyNumber == 2)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX02);
		newKuribou->SetPosY(Master::kKuribouPosY02);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou02 = false;
	}
	// 敵3体目のスポーン位置
	if (EnemyNumber == 3)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX03);
		newKuribou->SetPosY(Master::kKuribouPosY03);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou03 = false;
	}
	// 敵4体目のスポーン位置
	if (EnemyNumber == 4)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX04);
		newKuribou->SetPosY(Master::kKuribouPosY04);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou04 = false;
	}
	// 敵5体目のスポーン位置
	if (EnemyNumber == 5)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX05);
		newKuribou->SetPosY(Master::kKuribouPosY05);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou05 = false;
	}
	// 敵6体目のスポーン位置
	if (EnemyNumber == 6)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX06);
		newKuribou->SetPosY(Master::kKuribouPosY06);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou06 = false;
	}
	// 敵7体目のスポーン位置
	if (EnemyNumber == 7)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX07);
		newKuribou->SetPosY(Master::kKuribouPosY07);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou07 = false;
	}
	// 敵8体目のスポーン位置
	if (EnemyNumber == 8)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX08);
		newKuribou->SetPosY(Master::kKuribouPosY08);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou08 = false;
	}
	// 敵9体目のスポーン位置
	if (EnemyNumber == 9)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX09);
		newKuribou->SetPosY(Master::kKuribouPosY09);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou09 = false;
	}
	// 敵10体目のスポーン位置
	if (EnemyNumber == 10)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX10);
		newKuribou->SetPosY(Master::kKuribouPosY10);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou10 = false;
	}
	// 敵11体目のスポーン位置
	if (EnemyNumber == 11)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX11);
		newKuribou->SetPosY(Master::kKuribouPosY11);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou11 = false;
	}
	// 敵12体目のスポーン位置
	if (EnemyNumber == 12)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX12);
		newKuribou->SetPosY(Master::kKuribouPosY12);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou12 = false;
	}
	// 敵13体目のスポーン位置
	if (EnemyNumber == 13)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX13);
		newKuribou->SetPosY(Master::kKuribouPosY13);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou13 = false;
	}
	// 敵14体目のスポーン位置
	if (EnemyNumber == 14)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX14);
		newKuribou->SetPosY(Master::kKuribouPosY14);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou14 = false;
	}
	// 敵15体目のスポーン位置
	if (EnemyNumber == 15)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX15);
		newKuribou->SetPosY(Master::kKuribouPosY15);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou15 = false;
	}
	// 敵16体目のスポーン位置
	if (EnemyNumber == 16)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX16);
		newKuribou->SetPosY(Master::kKuribouPosY16);
		m_pKuribou.emplace_back(newKuribou);
		m_kuribou16 = false;
	}
}
