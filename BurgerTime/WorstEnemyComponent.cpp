#include "WorstEnemyComponent.h"
#include "structs.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"

void Burger::WorstEnemyComponent::Start()
{

	auto collider = GetAttachedGameObject()->GetComponent<dae::BoxColliderComponent>();
	assert(collider);

	dae::ColliderCallbacks colBack;
	colBack.OverlapEnterFunc = std::bind(&WorstEnemyComponent::OnCollisionEnter, this, std::placeholders::_1);
	colBack.OverlopExitFunc = std::bind(&WorstEnemyComponent::OnCollisionExit, this, std::placeholders::_1);
	colBack.OverlapStayFunc = std::bind(&WorstEnemyComponent::OnCollisionStay, this, std::placeholders::_1);

	collider->AddListener(colBack);
}

void Burger::WorstEnemyComponent::OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo)
{
	if (otherInfo->tag == "Shot") {
		std::cout << "hit\n";
		m_CurrState->Exit(*this);
		delete m_CurrState;
		m_CurrState = new HitState();
		m_CurrState->Entry(*this);
	}
	if (otherInfo->tag == "Bun") {

		glm::vec2 topCheck;
		topCheck.x = m_ColliderComponent->GetColliderInfo().m_ColliderRect.x 
			+ (m_ColliderComponent->GetColliderInfo().m_ColliderRect.width / 2.f);
		topCheck.y = m_ColliderComponent->GetColliderInfo().m_ColliderRect.y;

		//Bun detection
		if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, topCheck)) {
			m_IsDeath = true;
			m_CurrState->Exit(*this);
			delete m_CurrState;
			m_CurrState = new DeathState();
			m_CurrState->Entry(*this);
			//Death State
		}


	}
}

void Burger::WorstEnemyComponent::OnCollisionStay(const std::shared_ptr<dae::ColliderInfo> otherInfo)
{

}

void Burger::WorstEnemyComponent::OnCollisionExit(const std::shared_ptr<dae::ColliderInfo> otherInfo)
{

}
