#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "glm/detail/func_integer.hpp"
#include "GameObject.h"
#include "SceneColliders.h"
#include "BaseComponent.h"
#include "BoxColliderComponent.h"
#include "Scene.h"
#include "Time.h"

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

	switch (m_CurrentDirection) {
	case Direction::DOWN:

		colliderRect.x = newPos.x + (colliderRect.width / 2.f);
		colliderRect.y = newPos.y + (colliderRect.height);

		info = m_pParent->GetScene()->IsRectColliding(colliderRect, "Ladder");
		if (info) {

			newPos.y += m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		break;
	case Direction::UP:

		colliderRect.height /= 1.5f;
		colliderRect.x = newPos.x + (colliderRect.width / 2.f);
		colliderRect.y = newPos.y;


		info = m_pParent->GetScene()->IsRectColliding(colliderRect, "Ladder");
		if (info) {

			newPos.y -= m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		break;
	case Direction::LEFT:
		colliderRect.width /= 4.f;
		info = m_pParent->GetScene()->IsRectColliding(colliderRect, "Floor");
		if (info) {
			newPos.x -= m_Velocity * Time::GetInstance().GetDeltaTime();

			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		break;
	case Direction::RIGHT:
		colliderRect.x = newPos.x + (colliderRect.width / 4.f);
		colliderRect.width /= 4.f;
		info = m_pParent->GetScene()->IsRectColliding(colliderRect, "Floor");
		if (info) {
			newPos.x += m_Velocity * Time::GetInstance().GetDeltaTime();
			tr.SetPosition(newPos.x, newPos.y, 0.f);
		}
		break;

	}


}

void dae::MovementComponent::LateUpdate()
{

	

		

}

void dae::MovementComponent::SetNewDirection(Direction newDir)
{
	m_CurrentDirection = newDir;
}

