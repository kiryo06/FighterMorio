#pragma once
#include "BaseScene.h"

#include "game.h"
#include "MasterFunction.h"
#include <list>

class SceneManager;
class Map;
class Camera;
class Player;
class Kuribou;
class SystemEngineer;
class SceneChange;
class GameScene_1 : public BaseScene
{
public:
	GameScene_1(SceneManager& manager);
	virtual ~GameScene_1() override;
	void Init();
	void Update();
	void Draw();
	void SpawnPos();
	void EnemyPos(int EnemyNumber);
private:
	Map* m_pMap;
	Camera* m_pCamera;
	Player* m_pPlayer;
	std::list<Kuribou*>m_pKuribou;
	SystemEngineer* m_pSystemEngineer;
	SceneChange* m_pSceneChange;
	float PlayerPosX;
	int enemyNum;
	int m_FrameCounter;
	int m_Timer;
	bool m_Poozu;
	bool SetMenyu;
	bool PlayerDeath;
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