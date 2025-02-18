#include "SceneManager.h"
#include "TitleScene.h"

SceneManager::SceneManager()
{
	std::shared_ptr<TitleScene>pScene = std::make_shared<TitleScene>(*this);
	m_pScene = pScene;
	m_sceneState = SceneState::Title;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	m_pScene->Init();
}

void SceneManager::Update()
{
	m_pScene->Update();
}

void SceneManager::Draw()
{
	m_pScene->Draw();
}

void SceneManager::ChangeScene(const std::shared_ptr<BaseScene>& next)
{
	m_pScene = next;
	m_pScene->Init();
}
