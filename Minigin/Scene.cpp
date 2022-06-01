#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() {
	m_Objects.clear();
	std::cout << "fered\n";
};

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	object->SetScene(this);

	if (object->GetInitState() == false && m_IsStarted == true) {
		object->Start();
	}
	
}

void Scene::Update()
{
	m_SceneGrid.UpdateColliders();

	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Update();
		if (m_Objects[i]->GetDestroyFlag())
			DestroySceneObject(m_Objects[i]);

	}
}

void dae::Scene::Start()
{
	assert(m_IsStarted == false);

	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Start();
	}
	m_IsStarted = true;
}


const std::vector<std::shared_ptr<GameObject>> Scene::GetGameObjects(std::string lookupName)
{
	std::vector<std::shared_ptr<GameObject>> lookupVec;
	for (auto& element :  m_Objects)
	{
		if (element->GetName() == lookupName) {
			lookupVec.push_back(element);
		}
	}
	return lookupVec;
}

std::shared_ptr<dae::ColliderInfo> Scene::SceneRectcast(Rectf pos, glm::vec2 dir, float length, std::string tag, int steps /*= 10*/, const std::shared_ptr<ColliderInfo> colliderToIgnore /*= std::make_shared<ColliderInfo>()*/)
{
	return m_SceneGrid.RectCast(pos, dir, length, colliderToIgnore, tag, steps);
}

bool Scene::RemoveCollider(std::shared_ptr<ColliderInfo> colInfo)
{
	if (colInfo) {
		return m_SceneGrid.RemoveCollider(colInfo);

	}
	return false;
}

void Scene::DestroySceneObject(std::shared_ptr<GameObject> go)
{
	auto it = std::find(m_Objects.begin(), m_Objects.end(), go);
	m_Objects.erase(it);
}

std::shared_ptr<ColliderInfo> Scene::SceneRaycast(glm::vec2 pos, glm::vec2 dir, float length, std::string tag, int steps /*= 10*/, const std::shared_ptr<ColliderInfo> colliderToIgnore /*= std::make_shared<ColliderInfo>()*/)
{
	return m_SceneGrid.SceneRaycast(pos, dir, length, colliderToIgnore, tag, steps);

}

const std::vector < const dae::ColliderInfo* > Scene::GetAllCollidersWithTag(std::string tag) const
{
	return m_SceneGrid.GetAllCollidersWithTag(tag);
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

