#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>

void dae::SceneManager::Update()
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		m_Scenes[i]->Update();
		
	}
}

void dae::SceneManager::LateUpdate()
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		m_Scenes[i]->LateUpdate();
	}
}

void dae::SceneManager::Render()
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		m_Scenes[i]->Render();
		if (m_Scenes[i]->GetDestroyFlag()) {
			m_Scenes.erase(std::remove(m_Scenes.begin(), m_Scenes.end(), m_Scenes[i]), m_Scenes.end());
		}
	}
}

//void dae::SceneManager::SetActiveScene(const std::string& name)
//{
//	m_ActiveScene = *std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](std::shared_ptr<Scene>& currentLookupScene)
//		{
//			return currentLookupScene->GetSceneName() == name;
//		}
//	);
//}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	if (m_Scenes.size() == 1)
		m_ActiveScene = scene;
	return *scene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(const std::string& name)
{
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](std::shared_ptr<Scene>& scene) {return scene->GetSceneName() == name; });
	if (it != m_Scenes.end()) {
		return (*it);
	}
	return nullptr;
}

void dae::SceneManager::DestroyScene(const std::string& name)
{
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](std::shared_ptr<Scene>& scene) {return scene->GetSceneName() == name; });
	if (it != m_Scenes.end()) {
		(*it)->SetDestoryFlag();
	}
}
