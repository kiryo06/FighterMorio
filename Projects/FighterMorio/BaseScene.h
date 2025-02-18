#pragma once
#include <vector>

class SceneManager;
class BaseScene
{
public:
	BaseScene(SceneManager& manager);
	virtual ~BaseScene();
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	SceneManager& m_sceneManager;
	std::vector<int> GraphHandles;
	int m_Graph = 0;
};

