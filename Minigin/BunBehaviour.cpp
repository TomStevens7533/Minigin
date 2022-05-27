#include "MiniginPCH.h"
#include "BunBehaviour.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Scene.h"
#include "Time.h"
#include "ScoreDisplayComponent.h"
#include "ServiceLocator.h"


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
}

void dae::BunBehaviour::Start()
{
	auto colliderComponent = GetAttachedGameObject()->GetComponent<BoxColliderComponent>();
	assert(colliderComponent);

	if (colliderComponent) {
		colliderComponent->addObserver(this);
	}

}

void dae::BunBehaviour::SetFalling()
{
		

}

void dae::BunBehaviour::onNotify(const BaseComponent*, int event, EventArgs* args /*= nullptr*/)
{
	CollisionArgs* cArgs = static_cast<CollisionArgs*>(args);
	ColliderInfo info = cArgs->info;

	switch (event)
	{
	case EventType::OnCollisionEnter:
		if (info.tag == "Pepper") {
			m_IsPeterInCollFirst = true;
			m_EnterPeterPosX = info.m_ColliderRect.x;
		}
		else if (info.tag == "BunEnd" && m_IsFalling == true) {
			m_IsFalling = false;
			m_IsInFinalPos = true;
		}
		break;
	case EventType::OnCollisionExit:
		if (info.tag == "Pepper" && m_IsPeterInCollFirst) {
			m_IsFalling = true;
		}
		break;
	case EventType::OnCollisionStay:
		break;
	default:
		break;
	}
}

