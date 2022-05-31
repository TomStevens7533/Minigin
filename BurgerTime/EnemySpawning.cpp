#include "EnemySpawning.h"
#include "glm/glm.hpp"
#include "PrefabCreator.h"
#include "GameObject.h"
#include "Scene.h"
#include "EventType.h"
#include "AIBehaviourComponent.h"
#include "DeltaTime.h"

void Burger::EnemySpawnComponent::Start()
{
	m_MaxSpawnTime = m_BaseSpawnTime;

}

Burger::EnemySpawnComponent::EnemySpawnComponent(std::vector<point>& vec, std::map<std::string, EnemySpawnInfo>& enemyMap) 
	: m_SpawnPoints{vec}, m_EnemyMap{enemyMap}
{

}


void Burger::EnemySpawnComponent::onNotify(const BaseComponent* entity, int event, dae::EventArgs* args /*= nullptr*/)
{
	switch (event)
	{
	case PepperEvent::WORST_DIED:
		m_MaxSpawnTime += static_cast <float> (rand()) / static_cast <float> (m_RandSpawnTime) + m_BaseSpawnTime;
		break;
	default:
		break;
	}
}
void Burger::EnemySpawnComponent::LateUpdate()
{
	SpawnEnemy();
}


std::shared_ptr<dae::GameObject> Burger::EnemySpawnComponent::GetEnemyPrefab(const std::string& name, const point pos)
{
	if (name == "worst") {
		return PrefabCreator::CreatWorstEnemyrPrefab(pos);
	}
	else if (name == "egg") {
		return PrefabCreator::CreateEggEnemy(pos);
	}
	return nullptr;
}

void Burger::EnemySpawnComponent::SpawnEnemy()
{
	if (m_CurrentSpawnTime > m_MaxSpawnTime) {
	
		//Set to normal spawn timer
		m_MaxSpawnTime = m_BaseSpawnTime;
		m_CurrentSpawnTime = 0.f;
		
		for (auto& element : m_EnemyMap) {

			for (element.second.CurrentInStage; element.second.CurrentInStage < element.second.MaxInStage;)
			{
				int spawnPosIndex = (rand() % static_cast<int>(m_SpawnPoints.size()));
				auto enemyGO = GetEnemyPrefab(element.first, m_SpawnPoints[spawnPosIndex]);
				enemyGO->GetComponent<AIBehaviourComponent>()->addObserver(this);
				GetAttachedGameObject()->GetScene()->Add(enemyGO);
				++element.second.CurrentInStage;
				break;
			}


		}
	
	
	}
	else {
		//Add Timer
		m_CurrentSpawnTime += dae::Time::GetInstance().GetDeltaTime();
	}
	

}

