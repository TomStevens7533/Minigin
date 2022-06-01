#include "EnemySpawning.h"
#include "glm/glm.hpp"
#include "PrefabCreator.h"
#include "GameObject.h"
#include "Scene.h"
#include "EventType.h"
#include "AIBehaviourComponent.h"
#include "ScoreDisplayComponent.h"
#include "DeltaTime.h"
#include "BurgerEvents.h"

void Burger::EnemySpawnComponent::Start()
{
	m_MaxSpawnTime = m_BaseSpawnTime;

}

Burger::EnemySpawnComponent::EnemySpawnComponent(std::vector<point>& vec, std::map<EnemyType, EnemySpawnInfo>& enemyMap)
	: m_SpawnPoints{vec}, m_EnemyMap{enemyMap}
{

}


void Burger::EnemySpawnComponent::onNotify(const BaseComponent* entity, int event, dae::EventArgs* args /*= nullptr*/)
{
	
	switch (event)
	{
	case PepperEvent::ENEMY_DIED:
	{
		//Score to throw
		ScoreArgs sArgs;

		EnemyArgs* eArgs = static_cast<EnemyArgs*>(args);

		//Get random extra spawn time
		m_MaxSpawnTime += (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / m_RandSpawnTime))) + m_BaseSpawnTime;

		//-1 current in stage
		for (auto& element : m_EnemyMap) {
			if (element.first == eArgs->type) {
				--element.second.CurrentInStage;
				sArgs.scoreIncrease = element.second.Score;
			}
		}

		//throw score
		notify(this, PepperEvent::SCORE_INCREASE, &sArgs);
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


std::shared_ptr<dae::GameObject> Burger::EnemySpawnComponent::GetEnemyPrefab(const EnemyType type, const point pos, int points)
{
	switch (type)
	{
	case EnemyType::EGG:
		return PrefabCreator::CreateEggEnemy(pos, points);
		break;
	case EnemyType::WORST:
		return PrefabCreator::CreatWorstEnemyrPrefab(pos, points);
		break;
	case EnemyType::SPIKE:
		return PrefabCreator::CreateSpikey(pos, points);
		break;
	default:
		return nullptr;
		break;
	}
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

