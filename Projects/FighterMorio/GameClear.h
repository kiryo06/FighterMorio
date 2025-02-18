#pragma once
#include "game.h"
class GameClear
{
public:
	GameClear();
	~GameClear();
	void Init();
	void Update();
	void Draw();
private:
	int m_Graph_GAMECLEAR;
	int m_Graph_;
	int m_Graph_MojiA;
	int m_Graph_MojiB;
	int m_BrinkCounter;
};

