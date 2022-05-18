#include "MiniginPCH.h"
#include "HotDoggBehaviourComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "MovementComponent.h"

dae::HotDoggBehaviourComponent::HotDoggBehaviourComponent(std::string tagToFollow) : m_TagToFollow{tagToFollow}
{
}

void dae::HotDoggBehaviourComponent::Start()
{
	m_PlayerVec = GetAttachedGameObject()->GetScene()->GetAllCollidersWithTag(m_TagToFollow);
	m_HotDogMovement = GetAttachedGameObject()->GetComponent<MovementComponent>();
}

void dae::HotDoggBehaviourComponent::Update()
{
	glm::vec2 closestPos;
	glm::vec3 HotDoggPos = GetAttachedGameObject()->GetTransform().GetPosition();
	float distance = FLT_MAX;
	//if no player return
	if (m_PlayerVec.size() == 0)
		return;
	//Find closest Player
	for (size_t i = 0; i < m_PlayerVec.size(); i++)
	{
		//Calculate distance
		float xDiff = HotDoggPos.x - m_PlayerVec[i]->m_ColliderRect.x;
		float yDiff = HotDoggPos.y - m_PlayerVec[i]->m_ColliderRect.y;
		float currDistance = std::sqrt(xDiff * xDiff + yDiff * yDiff);
		if (currDistance < distance) {
			closestPos.x = m_PlayerVec[i]->m_ColliderRect.x;
			closestPos.y = m_PlayerVec[i]->m_ColliderRect.y;
			currDistance = distance;
		}
	}

	//Go to closest player pos
	 // 1st quadrant
	int quad{};
	if (closestPos.x > HotDoggPos.x && closestPos.y >= HotDoggPos.y)
		quad = 1;
	// 2nd quadrant
	else if (closestPos.x <= HotDoggPos.x && closestPos.y > HotDoggPos.y)
		quad = 2;
	// 3rd quadrant
	else if (closestPos.x < HotDoggPos.x && closestPos.y <= HotDoggPos.y)
		quad = 3;

	// 4th quadrant
	else if (closestPos.x >= HotDoggPos.x && closestPos.y < HotDoggPos.y)
		quad = 4;

	switch (quad)
	{
	case 1 :
		m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::RIGHT);
		m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::DOWN);
		break;
	case 2:
		m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::LEFT);
		m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::DOWN);
		break;
	case 3:
		m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::LEFT);
		m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::UP);
		break;
	case 4:
		m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::RIGHT);
		m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::UP);
		break;
	default:
		break;
	}


}

