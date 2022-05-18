#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "glm/detail/func_integer.hpp"
#include "GameObject.h"
#include "SceneColliders.h"
#include "BaseComponent.h"
#include "BoxColliderComponent.h"
#include "Scene.h"
#include "Time.h"
#include "ServiceLocator.h"

dae::MovementComponent::MovementComponent(float movementVelocity) : m_Velocity{movementVelocity}
{

}

void dae::MovementComponent::Start()
{
	m_ColliderComponent = GetAttachedGameObject()->GetComponent<BoxColliderComponent>();
}

void dae::MovementComponent::Update()
{
	Transform& tr = m_pParent->GetTransform();
	glm::vec2 newPos;
	newPos = tr.GetPosition();
	glm::vec2 colliderDimensions = m_ColliderComponent->GetDimension();
	Rectf colliderRect;
	colliderRect = Rectf{ newPos.x, newPos.y, colliderDimensions.x, colliderDimensions.y };

	std::shared_ptr<ColliderInfo> info;
	glm::vec2 lookUpPos = newPos;
	//Horizontal
	switch (m_CurrentHorizonDirection) {
	case HorizontalDirection::LEFT:
		colliderRect.x = newPos.x -(colliderRect.width);
		colliderRect.y += colliderRect.height / 2.f;
		colliderRect.height /= 2.f;



		info = m_pParent->GetScene()->IsRectColliding(colliderRect, "Floor");
		if (info) {
			newPos.x -= m_Velocity * Time::GetInstance().GetDeltaTime();

			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		break;
	case HorizontalDirection::RIGHT:
		colliderRect.x = newPos.x + (colliderRect.width);
		colliderRect.y += colliderRect.height / 2.f;
		colliderRect.height /= 2.f;

		info = m_pParent->GetScene()->IsRectColliding(colliderRect, "Floor");
		if (info) {
			newPos.x += m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		break;

	}
	//vertical
	switch (m_CurrentVertoicalDirection)
	{
	case VerticalDirection::DOWN:
		lookUpPos.x += colliderRect.width / 2.f;
		lookUpPos.y += colliderRect.height;

		info = m_pParent->GetScene()->IsPointInCollider(lookUpPos, "Ladder");
		if (info) {

			newPos.y += m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		break;
	case VerticalDirection::UP:

		lookUpPos.x += colliderRect.width / 2.f;
		lookUpPos.y += colliderRect.height /1.f;

		info = m_pParent->GetScene()->IsPointInCollider(lookUpPos, "Ladder");
		if (info) {

			newPos.y -= m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		break;

	default:
		break;
	}


}

void dae::MovementComponent::LateUpdate()
{

	

		

}

void dae::MovementComponent::SetNewVerticalDirection(VerticalDirection newDir)
{
	m_CurrentVertoicalDirection = newDir;
}

void dae::MovementComponent::SetNewHorizontalDirection(HorizontalDirection newDir)
{
	m_CurrentHorizonDirection = newDir;
}

