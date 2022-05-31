#include "EnemySpawning.h"
#include "glm/glm.hpp"
#include "PrefabCreator.h"
#include "GameObject.h"
#include "Scene.h"
#include "EventType.h"
#include "AIBehaviourComponent.h"
#include "DeltaTime.h"
#include "ScoreDisplayComponent.h"

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
	EnemyArgs* eArgs;
	switch (event)
	{
	case PepperEvent::Enemy_Died:
		eArgs = static_cast<EnemyArgs*>(args);
		m_MaxSpawnTime += (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / m_RandSpawnTime))) + m_BaseSpawnTime;

		//-1 current in stage
		for (auto& element : m_EnemyMap) {
			if (element.first == eArgs->name) {
				--element.second.CurrentInStage;
			}
		}
		break;
	default:
		break;
	}
}
void Burger::EnemySpawnComponent::LateUpdate()
{
	SpawnEnemy();
}


std::shared_ptr<dae::GameObject> Burger::EnemySpawnComponent::GetEnemyPrefab(const std::string& name, const point pos, int points)
{
	if (name == "worst") {
		return PrefabCreator::CreatWorstEnemyrPrefab(pos, points);
	}
	else if (name == "egg") {
		return PrefabCreator::CreateEggEnemy(pos, points);
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
				auto enemyGO = GetEnemyPrefab(element.first, m_SpawnPoints[spawnPosIndex], element.second.Score);
				auto comp = enemyGO->GetComponent<AIBehaviourComponent>();
				comp->addObserver(this);
				if (m_pScoreUI != nullptr) {
					comp->addObserver(m_pScoreUI);
				}
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

