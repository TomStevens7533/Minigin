#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "glm/detail/func_integer.hpp"
#include "GameObject.h"
#include "SceneColliders.h"
#include "BaseComponent.h"
#include "BoxColliderComponent.h"
#include "Scene.h"
#include "DeltaTime.h"
#include "ServiceLocator.h"
#include "MathHelper.h"

using namespace dae;
Burger::MovementComponent::MovementComponent(float movementVelocity) : m_Velocity{movementVelocity}
{

}

void Burger::MovementComponent::Start()
{
	m_ColliderComponent = GetAttachedGameObject()->GetComponent<dae::BoxColliderComponent>();

	if (m_ColliderComponent) {
		dae::ColliderCallbacks colBack;
		colBack.OverlapStayFunc = std::bind(&MovementComponent::OnCollisionStay, this, std::placeholders::_1);

		m_ColliderComponent->AddListener(colBack);
	}
}

void Burger::MovementComponent::Update()
{
	if (m_IsDisabled) {
		std::cout << "disable\n";
		return;
	}

	Transform& tr = m_pParent->GetTransform();
	glm::vec2 newPos;
	newPos = tr.GetPosition();
	glm::vec2 lookUpPos = newPos;
	//Horizontal
	switch (m_CurrentDir) {
	case Direction::LEFT:
		if (m_IsOnFloorLeft || m_IsCollisionDisabled) {
			newPos.x -= m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		else
			m_CurrentDir = Direction::NONE;
		break;
	case Direction::RIGHT:
		if (m_IsOnFloorRight || m_IsCollisionDisabled) {
			newPos.x += m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		else
			m_CurrentDir = Direction::NONE;
		break;

	case Direction::DOWN:
		if (m_IsOnLadderDown || m_IsCollisionDisabled) {
			newPos.y += m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		else
			m_CurrentDir = Direction::NONE;

		break;
	case Direction::UP:
		if (m_IsOnLadderUp || m_IsCollisionDisabled) {
			newPos.y -= m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		else
			m_CurrentDir = Direction::NONE;
		break;
	default:
		break;
	}


}

void Burger::MovementComponent::LateUpdate()
{

	//Reser movement
	m_IsOnLadderDown = false;
	m_IsOnLadderUp = false;
	m_IsOnFloorRight = false;
	m_IsOnFloorLeft = false;

		

}

void Burger::MovementComponent::SetNewDirection(Direction newDir)
{
	m_CurrentDir = newDir;
}

void Burger::MovementComponent::OnCollisionStay(const std::shared_ptr<dae::ColliderInfo> otherInfo)
{
	glm::vec2 searchPos1;
	glm::vec2 searchPos2;
	dae::ColliderInfo info = m_ColliderComponent->GetColliderInfo();


	if (otherInfo->tag == "Ladder") {

		//UP
		searchPos1.x = info.m_ColliderRect.x + (info.m_ColliderRect.width / 2.f);
		searchPos1.y = info.m_ColliderRect.y + (info.m_ColliderRect.height / 2.f);

		//Down					
		searchPos2.x = info.m_ColliderRect.x + (info.m_ColliderRect.width / 2.f);
		searchPos2.y = info.m_ColliderRect.y + info.m_ColliderRect.height;

		if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, searchPos1)) {

			m_IsOnLadderUp = true;
		}
		if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, searchPos2)) {
			m_IsOnLadderDown = true;

		}
	}
	if (otherInfo->tag == "Floor") {

		//right
		searchPos1.x = info.m_ColliderRect.x + (info.m_ColliderRect.width / 4.f);
		searchPos1.y = info.m_ColliderRect.y + (info.m_ColliderRect.height);

		////left
		searchPos2.x = info.m_ColliderRect.x + ((info.m_ColliderRect.width));
		searchPos2.y = info.m_ColliderRect.y + info.m_ColliderRect.height;

		if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, searchPos2)) {
			m_IsOnFloorRight = true;
		}
		if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, searchPos1)) {
			m_IsOnFloorLeft = true;
		}


	}
}
