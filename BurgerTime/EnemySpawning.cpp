#include "EnemySpawning.h"
#include "glm/glm.hpp"
#include "PrefabCreator.h"
#include "GameObject.h"
#include "Scene.h"
#include "EventType.h"
#include "AIBehaviourComponent.h"

void Burger::EnemySpawnComponent::Start()
{
	//Spawn worst
	SpawnEnemies();
}

Burger::EnemySpawnComponent::EnemySpawnComponent(std::vector<point>& vec) : m_SpawnPoints{vec}
{

}

void Burger::EnemySpawnComponent::onNotify(const BaseComponent* entity, int event, dae::EventArgs* args /*= nullptr*/)
{
	switch (event)
	{
	case PepperEvent::WORST_DIED:
		--m_CurrentWorstInStage;
		SpawnEnemies();
		break;
	default:
		break;
	}
}

void Burger::EnemySpawnComponent::SpawnEnemies()
{
	for (m_CurrentWorstInStage; m_CurrentWorstInStage < m_MaxWorstInStage;)
	{
		int spawnPosIndex = (m_CurrentWorstInStage % static_cast<int>(m_SpawnPoints.size()));
		auto worstGo = PrefabCreator::CreatWorstEnemyrPrefab(m_SpawnPoints[spawnPosIndex]);
		worstGo->GetComponent<AIBehaviourComponent>()->addObserver(this);
		GetAttachedGameObject()->GetScene()->Add(worstGo);
		++m_CurrentWorstInStage;
	}
}

