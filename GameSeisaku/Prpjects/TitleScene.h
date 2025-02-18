#pragma once
#include "BaseScene.h"

class TitlePlayMovie;
class SceneManager;
class TitleScene : public BaseScene
{
public:
	TitleScene(SceneManager& manager);
	virtual ~TitleScene() override;
	void Init();
	void Update();
	void Draw();
private:
	TitlePlayMovie* m_pTitlePlayMovie;
	int m_Graph;
	int m_TitleStart;
	int m_BrinkCounter;
};

