#include "MiniginPCH.h"
#include "BunBehaviour.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Scene.h"
#include "Time.h"
#include "ScoreDisplayComponent.h"
#include "ServiceLocator.h"
#include "MathHelper.h"


void dae::BunBehaviour::Render() const
{

}

void dae::BunBehaviour::Update()
{
	//Set burger falling
	if (m_IsFalling && m_IsInFinalPos == false) {
		glm::vec3 newPos = m_pParent->GetTransform().GetPosition();
		newPos.y += m_Velocity * Time::GetInstance().GetDeltaTime();
		m_pParent->GetTransform().SetPosition(newPos.x, newPos.y, newPos.z);
	}


}

void dae::BunBehaviour::LateUpdate()
{
	if (m_ScoreToThrow > 0) {
		ScoreArgs args;
		args.scoreIncrease = m_ScoreToThrow;
		notify(this, PepperEvent::SCORE_INCREASE, &args);
		m_ScoreToThrow = 0;
	}
}

void dae::BunBehaviour::Start()
{
	auto colliderComponent = GetAttachedGameObject()->GetComponent<BoxColliderComponent>();
	assert(colliderComponent);



	ColliderCallbacks colBack;
	colBack.OverlapEnterFunc = std::bind(&BunBehaviour::OnCollisionEnter, this, std::placeholders::_1);
	colBack.OverlopExitFunc = std::bind(&BunBehaviour::OnCollisionExit, this, std::placeholders::_1);
	colBack.OverlapStayFunc = std::bind(&BunBehaviour::OnCollisionStay, this, std::placeholders::_1);

	colliderComponent->AddListener(colBack);
}

void dae::BunBehaviour::SetFalling()
{
		

}

void dae::BunBehaviour::OnCollisionStay(const std::shared_ptr<ColliderInfo> otherInfo)
{

}

void dae::BunBehaviour::OnCollisionEnter(const std::shared_ptr<ColliderInfo> otherInfo)
{
	if (m_IsInFinalPos)
		return;


	ColliderInfo info = *otherInfo;
	if (info.tag == "Pepper") {
		m_IsPeterInCollFirst = true;
		m_EnterPeterPosX = info.m_ColliderRect.x;
	}
	else if ((info.tag == "BunEnd" || info.tag == "Floor") && m_IsFalling == true) {
		m_IsFalling = false;
		m_ScoreToThrow += 50;
		if (info.tag == "BunEnd")
			m_IsInFinalPos = true;
	}
	else if (info.tag == "Bun" && m_IsFalling == false) {
		m_IsFalling = true;
	}
	else if ((info.tag == "Enemy") && m_IsFalling == true) {

		if (m_ScoreToThrow == 0)
			m_ScoreToThrow = 500;
		else
			m_ScoreToThrow = m_ScoreToThrow * 2;
	}

}

void dae::BunBehaviour::OnCollisionExit(const std::shared_ptr<ColliderInfo> otherInfo)
{
	if (otherInfo->tag == "Pepper" && m_IsPeterInCollFirst && !MathHelper::AreEqual(m_EnterPeterPosX, otherInfo->m_ColliderRect.x, 2.f)) {
		m_IsFalling = true;
	}
}
