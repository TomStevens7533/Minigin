#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
	object->SetScene(this);
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void dae::Scene::Start()
{
	for (const auto& object : m_Objects)
	{
		object->Start();
	}
}

std::vector < std::shared_ptr<dae::ColliderInfo> > Scene::GetAllCollidersWithTag(std::string tag)
{
	return m_SceneGrid.GetAllCollidersWithTag(tag);
}

std::shared_ptr<dae::ColliderInfo> Scene::SceneRaycast(glm::vec2 pos, glm::vec2 dir, float length, std::string tag, int steps, const std::shared_ptr<ColliderInfo> colliderToIgnore)
{
	return m_SceneGrid.SceneRaycast(pos, dir, length, colliderToIgnore,tag, steps);
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}
}

