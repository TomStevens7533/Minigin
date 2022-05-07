#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "glm/detail/func_integer.hpp"
#include "GameObject.h"
#include "SceneColliders.h"
#include "BaseComponent.h"
#include "BoxColliderComponent.h"
#include "Scene.h"

dae::MovementComponent::MovementComponent(float movementVelocity) : m_Velocity{movementVelocity}
{

}

void dae::MovementComponent::Start()
{
	m_ColliderComponent = GetAttachedGameObject()->GetComponent<BoxColliderComponent>();
}

void dae::MovementComponent::LateUpdate()
{

	Transform& tr = m_pParent->GetTransform();
	glm::vec2 newPos;
	newPos = tr.GetPosition();
	glm::vec2 colliderDimensions = m_ColliderComponent->GetDimension();
	Rectf colliderRect;
	colliderRect = Rectf{ newPos.x, newPos.y, colliderDimensions.x, colliderDimensions.y };

	ColliderInfo* info;

		switch (m_CurrentDirection) {
		case Direction::DOWN:
			info = m_pParent->GetScene()->IsRectColliding(colliderRect, "Ladder");
			if (info != nullptr) {

				newPos.y += m_Velocity;
				tr.SetPosition(newPos.x, newPos.y, 0.f);
			}
			break;
		case Direction::UP:
			info = m_pParent->GetScene()->IsRectColliding(colliderRect, "Ladder");
			if (info != nullptr) {

				newPos.y -= m_Velocity;
				tr.SetPosition(newPos.x, newPos.y, 0.f);
			}
			break;
		case Direction::LEFT:
			info = m_pParent->GetScene()->IsRectColliding(colliderRect, "Floor");
			if (info != nullptr) {
				newPos.x -= m_Velocity;

				tr.SetPosition(newPos.x, newPos.y, 0.f);
			}
			break;
		case Direction::RIGHT:
			info = m_pParent->GetScene()->IsRectColliding(colliderRect, "Floor");
			if (info != nullptr) {
				newPos.x += m_Velocity;
				tr.SetPosition(newPos.x, newPos.y, 0.f);
			}
			break;

		}
	


		

}

void dae::MovementComponent::SetNewDirection(Direction newDir)
{
	m_CurrentDirection = newDir;
}

