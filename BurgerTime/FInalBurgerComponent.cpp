#include "FInalBurgerComponent.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "EventType.h"

void Burger::FinalBurgerComponent::Render() const
{

}

void Burger::FinalBurgerComponent::Update()
{

}

void Burger::FinalBurgerComponent::LateUpdate()
{

}

void Burger::FinalBurgerComponent::Start()
{

	m_BoxColliderComp = GetAttachedGameObject()->GetComponent<dae::BoxColliderComponent>();
	assert(m_BoxColliderComp);
	dae::ColliderCallbacks colBack;
	colBack.OverlapEnterFunc = std::bind(&FinalBurgerComponent::OnCollisionEnter, this, std::placeholders::_1);

	m_BoxColliderComp->AddListener(colBack);
}

Burger::FinalBurgerComponent::FinalBurgerComponent(int fullBurger) :m_MaxBunPieces{fullBurger}
{

}


void Burger::FinalBurgerComponent::OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo)
{
	if (otherInfo->tag == "Bun") {
		m_CurrentBunPieces++;
		if (m_CurrentBunPieces >= m_MaxBunPieces) {
			notify(this, PepperEvent::BURGER_COMPLETE);
			return;
		}
		float x = m_BoxColliderComp->GetColliderInfo().m_ColliderRect.x;
		float newY = m_BoxColliderComp->GetColliderInfo().m_ColliderRect.y - otherInfo->m_ColliderRect.height;
		m_BoxColliderComp->SetNewPos(glm::vec2{ x , newY });
		m_BoxColliderComp->SetNewHeight(m_BoxColliderComp->GetColliderInfo().m_ColliderRect.height + otherInfo->m_ColliderRect.height);
	}
}


