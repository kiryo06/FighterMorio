#pragma once
#include "BaseScene.h"

class SceneManager;
class StageSelectionScene : public BaseScene
{
public:
	StageSelectionScene(SceneManager& manager);
	virtual ~StageSelectionScene() override;
	void Init();
	void Update();
	void Draw();


};

