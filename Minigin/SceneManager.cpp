#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>

void dae::SceneManager::Update()
{
	m_ActiveScene->Update();
}

void dae::SceneManager::LateUpdate()
{
	m_ActiveScene->LateUpdate();
}

void dae::SceneManager::Render()
{
	m_ActiveScene->Render();
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	m_ActiveScene = *std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](std::shared_ptr<Scene>& currentLookupScene)
		{
			return currentLookupScene->GetSceneName() == name;
		}
	);
}

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
