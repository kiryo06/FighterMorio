#pragma once
#include "game.h"
class SceneChange
{
public:
	SceneChange();
	~SceneChange();
	void Init();
	void Update();
	void Draw();
	void SetDeath(bool isdeath) { ChangeDeath = isdeath; }
	void SetClear(bool isclear) { ChangeClear = isclear; }
	int GetChange()const {return isSceneChange; }
private:
	float w, h;
	int x; 
	int y;
	int X;
	int Y;
	bool ChangeDeath;
	bool ChangeClear;
	bool isSceneChange;
	int m_FrameCounter;
};

