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
	std::shared_ptr<ColliderInfo> info;
	glm::vec2 lookUpPos = newPos;
	//Horizontal
	switch (m_CurrentHorizonDirection) {
	case HorizontalDirection::LEFT:
		newPos.x -= m_Velocity * Time::GetInstance().GetDeltaTime();
		tr.SetPosition(newPos.x, newPos.y, 0.f);
		break;
	case HorizontalDirection::RIGHT:

		
			newPos.x += m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		
		
		
		break;
	default:
		m_IsMovingHorizontally = false;
		break;
	}
	//vertical
	switch (m_CurrentVertoicalDirection)
	{
	case VerticalDirection::DOWN:
		
			newPos.y += m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		
		break;
	case VerticalDirection::UP:

		

			newPos.y -= m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
	
		break;
	default:
		m_IsMovingVertically = false;
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


glm::vec2 dae::MovementComponent::GetCenterPos() const
{
	Transform& tr = m_pParent->GetTransform();
	glm::vec2 newPos;
	newPos = tr.GetPosition();
	glm::vec2 colliderDimensions = m_ColliderComponent->GetDimension();
	return glm::vec2{ newPos.x + (colliderDimensions.x / 2.f), newPos.y + (colliderDimensions.y / 2.f) };
}

void dae::MovementComponent::SetNewHorizontalDirection(HorizontalDirection newDir)
{
	m_CurrentHorizonDirection = newDir;
}

