#include "MiniginPCH.h"
#include "BunBehaviour.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Scene.h"
#include "DeltaTime.h"
#include "ServiceLocator.h"
#include "MathHelper.h"
#include "EventType.h"
#include "BurgerEvents.h"
#include "BaseComponent.h"
#include "AIBehaviourComponent.h"


void Burger::BunBehaviour::Render() const
{

}

void Burger::BunBehaviour::Update()
{
	//Set burger falling
	if (m_IsFalling && m_IsInFinalPos == false) {
		glm::vec3 newPos = m_pParent->GetTransform().GetPosition();
		newPos.y += m_Velocity * dae::Time::GetInstance().GetDeltaTime();
		m_pParent->GetTransform().SetPosition(newPos.x, newPos.y, newPos.z);
	}


}

void Burger::BunBehaviour::LateUpdate()
{
	if (m_ScoreToThrow > 0) {
		ScoreArgs args;
		args.scoreIncrease = m_ScoreToThrow;
		notify(this, PepperEvent::SCORE_INCREASE, &args);
		m_ScoreToThrow = 0;
	}
}

void Burger::BunBehaviour::Start()
{
	auto colliderComponent = GetAttachedGameObject()->GetComponent<dae::BoxColliderComponent>();
	assert(colliderComponent);



	dae::ColliderCallbacks colBack;
	colBack.OverlapEnterFunc = std::bind(&BunBehaviour::OnCollisionEnter, this, std::placeholders::_1);
	colBack.OverlopExitFunc = std::bind(&BunBehaviour::OnCollisionExit, this, std::placeholders::_1);
	colBack.OverlapStayFunc = std::bind(&BunBehaviour::OnCollisionStay, this, std::placeholders::_1);

	colliderComponent->AddListener(colBack);
}
void Burger::BunBehaviour::OnCollisionStay(const std::shared_ptr<dae::ColliderInfo> otherInfo)
{
	dae::ColliderInfo info = *otherInfo;
	if ((info.tag == "Enemy") && m_IsFalling == true) {
		point enemyPos = point{ info.m_ColliderRect.x, info.m_ColliderRect.y - info.m_ColliderRect.height };

		if (enemyPos.y < GetAttachedGameObject()->GetTransform().GetPosition().y) {
			//TODO DECOUPLE if possible
			auto enemyBeh = otherInfo->m_pAttachedGameObject->GetComponent<AIBehaviourComponent>();
			if (enemyBeh != nullptr) {
				enemyBeh->SetFallState(m_Velocity);
			}
			m_EnemyOnBun = true;
		}
	}
}

void Burger::BunBehaviour::OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo)
{
	if (m_IsInFinalPos)
		return;


	dae::ColliderInfo info = *otherInfo;
	if (info.tag == "Pepper") {
		m_IsPeterInCollFirst = true;
		m_EnterPeterPosX = info.m_ColliderRect.x;
	}
	else if (info.tag == "Floor" && m_IsFalling == true && m_EnemyOnBun == false) {
		m_IsFalling = false;
		m_ScoreToThrow += 50;
	}
	else if ((info.tag == "BunEnd") && m_IsFalling == true) {
		m_IsFalling = false;
		m_ScoreToThrow += 50;
		m_IsInEndPos = true;
	}
	else if (info.tag == "Bun" && m_IsFalling == false &&  m_IsInEndPos == false ) {
		//only if bun is on top
		m_IsFalling = true;
	}
	else if ((info.tag == "Enemy") && m_IsFalling == true) {
		point enemyPos = point{info.m_ColliderRect.x, info.m_ColliderRect.y};

		if (m_ScoreToThrow == 0)
			m_ScoreToThrow = 500;
		else
			m_ScoreToThrow = m_ScoreToThrow * 2;
	}
	 
	else if ((info.tag == "Enemy") && m_IsFalling == true) {
		point enemyPos = point{ info.m_ColliderRect.x, info.m_ColliderRect.y };

		if (m_ScoreToThrow == 0)
			m_ScoreToThrow = 500;
		else
			m_ScoreToThrow = m_ScoreToThrow * 2;
	}
}

void Burger::BunBehaviour::OnCollisionExit(const std::shared_ptr<dae::ColliderInfo> otherInfo)
{
	if (otherInfo->tag == "Pepper" && m_IsPeterInCollFirst && !MathHelper::AreEqual(m_EnterPeterPosX, otherInfo->m_ColliderRect.x, 2.f)) {
		m_IsFalling = true;
	}
}
