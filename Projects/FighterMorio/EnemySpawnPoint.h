#pragma once
#include "game.h"
#include <list>
class Player;
class Kuribou;
class Camera;
class EnemySpawnPoint
{
public:
	EnemySpawnPoint();
	~EnemySpawnPoint();
	void Init();
	void Update();
	void Draw();
	void SpawnPos();
	void EnemyPos(int EnemyNumber);
private:
	Player* m_pPlayer;
	std::list<Kuribou*>m_pKuribou;
	Camera* m_pCamera;
	int PlayerPosX;
	bool m_kuribou00;
	bool m_kuribou01;
	bool m_kuribou02;
	bool m_kuribou03;
	bool m_kuribou04;
	bool m_kuribou05;
	bool m_kuribou06;
	bool m_kuribou07;
	bool m_kuribou08;
	bool m_kuribou09;
	bool m_kuribou10;
	bool m_kuribou11;
	bool m_kuribou12;
	bool m_kuribou13;
	bool m_kuribou14;
	bool m_kuribou15;
	bool m_kuribou16;
};

