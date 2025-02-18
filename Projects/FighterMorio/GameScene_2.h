#pragma once
#include "BaseScene.h"

#include "game.h"
#include <list>

class SceneManager;
class Map;
class Camera;
class Player;
class Kuribou;
class SystemEngineer;
class GameScene_2 : public BaseScene
{
public:
	GameScene_2(SceneManager& manager);
	virtual ~GameScene_2() override;
	void Init();
	void Update();
	void Draw();
private:
	Map* m_pMap;
	Camera* m_pCamera;
	Player* m_pPlayer;
	std::list<Kuribou*>m_pKuribou;
	SystemEngineer* m_pSystemEngineer;
};
