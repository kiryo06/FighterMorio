#include "EnemySpawnPoint.h"
#include "DxLib.h"
#include "Player.h"
#include "Kuribou.h"
#include "Camera.h"
#include "MasterFunction.h"

EnemySpawnPoint::EnemySpawnPoint():
	m_pPlayer(new Player),
	m_pKuribou(),
	m_pCamera(new Camera),
	PlayerPosX(0),
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

EnemySpawnPoint::~EnemySpawnPoint()
{
}

void EnemySpawnPoint::Init()
{
	for (auto& item : m_pKuribou)
	{
		item->Init(1);
	}
}

void EnemySpawnPoint::Update()
{
	//Kuribou* newKuribou = new Kuribou;
	//newKuribou->Init(1);
	SpawnPos();
	//m_pKuribou.emplace_back(newKuribou);
	for (auto& item : m_pKuribou)
	{
		item->Update(1, m_pPlayer);
	}
}

void EnemySpawnPoint::Draw()
{
	for (auto& item : m_pKuribou)
	{
		item->Draw(m_pCamera);
	}
}

void EnemySpawnPoint::SpawnPos()
{
	PlayerPosX = m_pPlayer->GetPlayerPos().x;
	
	// 1体目
	if (PlayerPosX >= Master::kSpawnPosX01)
	{
		EnemyPos(1);
	}
	// 2体目
	if (PlayerPosX >= Master::kSpawnPosX02)
	{
		EnemyPos(2);
	}
	// 3体目
	if (PlayerPosX >= Master::kSpawnPosX03)
	{
		EnemyPos(3);
	}
	// 4体目
	if (PlayerPosX >= Master::kSpawnPosX04)
	{
		EnemyPos(4);
	}
	// 5体目
	if (PlayerPosX >= Master::kSpawnPosX05)
	{
		EnemyPos(5);
	}
	// 6体目
	if (PlayerPosX >= Master::kSpawnPosX06)
	{
		EnemyPos(6);
	}
	// 7体目
	if (PlayerPosX >= Master::kSpawnPosX07)
	{
		EnemyPos(7);
	}
	// 8体目
	if (PlayerPosX >= Master::kSpawnPosX08)
	{
		EnemyPos(8);
	}
	// 9体目
	if (PlayerPosX >= Master::kSpawnPosX09)
	{
		EnemyPos(9);
	}
	// 10体目
	if (PlayerPosX >= Master::kSpawnPosX10)
	{
		EnemyPos(10);
	}
	// 11体目
	if (PlayerPosX >= Master::kSpawnPosX11)
	{
		EnemyPos(11);
	}
	// 12体目
	if (PlayerPosX >= Master::kSpawnPosX12)
	{
		EnemyPos(12);
	}
	// 13体目
	if (PlayerPosX >= Master::kSpawnPosX13)
	{
		EnemyPos(13);
	}
	// 14体目
	if (PlayerPosX >= Master::kSpawnPosX14)
	{
		EnemyPos(14);
	}
	// 15体目
	if (PlayerPosX >= Master::kSpawnPosX15)
	{
		EnemyPos(15);
	}
	// 16体目
	if (PlayerPosX >= Master::kSpawnPosX16)
	{
		EnemyPos(16);
	}
}

void EnemySpawnPoint::EnemyPos(int EnemyNumber)
{
	// 敵1体目のスポーン位置
	if (EnemyNumber == 1)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX01);
		newKuribou->SetPosY(Master::kKuribouPosY01);
		m_pKuribou.emplace_back(newKuribou);

	}
	// 敵2体目のスポーン位置
	if (EnemyNumber == 2)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX02);
		newKuribou->SetPosY(Master::kKuribouPosY02);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵3体目のスポーン位置
	if (EnemyNumber == 3)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX03);
		newKuribou->SetPosY(Master::kKuribouPosY03);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵4体目のスポーン位置
	if (EnemyNumber == 4)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX04);
		newKuribou->SetPosY(Master::kKuribouPosY04);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵5体目のスポーン位置
	if (EnemyNumber == 5)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX05);
		newKuribou->SetPosY(Master::kKuribouPosY05);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵6体目のスポーン位置
	if (EnemyNumber == 6)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX06);
		newKuribou->SetPosY(Master::kKuribouPosY06);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵7体目のスポーン位置
	if (EnemyNumber == 7)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX07);
		newKuribou->SetPosY(Master::kKuribouPosY07);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵8体目のスポーン位置
	if (EnemyNumber == 8)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX08);
		newKuribou->SetPosY(Master::kKuribouPosY08);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵9体目のスポーン位置
	if (EnemyNumber == 9)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX09);
		newKuribou->SetPosY(Master::kKuribouPosY09);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵10体目のスポーン位置
	if (EnemyNumber == 10)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX10);
		newKuribou->SetPosY(Master::kKuribouPosY10);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵11体目のスポーン位置
	if (EnemyNumber == 11)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX11);
		newKuribou->SetPosY(Master::kKuribouPosY11);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵12体目のスポーン位置
	if (EnemyNumber == 12)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX12);
		newKuribou->SetPosY(Master::kKuribouPosY12);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵13体目のスポーン位置
	if (EnemyNumber == 13)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX13);
		newKuribou->SetPosY(Master::kKuribouPosY13);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵14体目のスポーン位置
	if (EnemyNumber == 14)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX14);
		newKuribou->SetPosY(Master::kKuribouPosY14);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵15体目のスポーン位置
	if (EnemyNumber == 15)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX15);
		newKuribou->SetPosY(Master::kKuribouPosY15);
		m_pKuribou.emplace_back(newKuribou);
	}
	// 敵16体目のスポーン位置
	if (EnemyNumber == 16)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX16);
		newKuribou->SetPosY(Master::kKuribouPosY16);
		m_pKuribou.emplace_back(newKuribou);
	}
}
