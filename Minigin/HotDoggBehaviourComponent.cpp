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


	int quad = GetPlayerQuadrant();
	switch (quad)
	{
	case 1:
		m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::RIGHT);
		break;
	case 2:
		m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::LEFT);
		break;
	case 3:
		m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::LEFT);
		break;
	case 4:
		m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::RIGHT);
		break;
	default:
		break;
	}


}

void dae::HotDoggBehaviourComponent::Update()
{
	glm::vec2 closestPos;
	glm::vec3 HotDoggPos = GetAttachedGameObject()->GetTransform().GetPosition();
	float distance = FLT_MAX;
	//if no player return
	if (m_PlayerVec.size() == 0)
		return;
	float xDiff{};
	float yDiff{};

	//Find closest Player
	for (size_t i = 0; i < m_PlayerVec.size(); i++)
	{
		//Calculate distance with center point of player
		xDiff = HotDoggPos.x - (m_PlayerVec[i]->m_ColliderRect.x + ((m_PlayerVec[i]->m_ColliderRect.width / 2.f)));
		yDiff = HotDoggPos.y - (m_PlayerVec[i]->m_ColliderRect.y + (m_PlayerVec[i]->m_ColliderRect.height / 2.f));
		float currDistance = std::sqrt(xDiff * xDiff + yDiff * yDiff);
		if (currDistance < distance) {
			closestPos.x = m_PlayerVec[i]->m_ColliderRect.x + ((m_PlayerVec[i]->m_ColliderRect.width / 2.f));
			closestPos.y = m_PlayerVec[i]->m_ColliderRect.y + (m_PlayerVec[i]->m_ColliderRect.height / 2.f);
			currDistance = distance;
		}
	}

	if (m_HotDogMovement->GetIsMovingVertically() && (m_HotDogMovement->GetIsMovingHorizontally() == false)) {
	//Go to closest player pos
	// 1st quadrant
		if (closestPos.x > HotDoggPos.x && closestPos.y >= HotDoggPos.y)
			m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::RIGHT);
		// 2nd quadrant
		else if (closestPos.x <= HotDoggPos.x && closestPos.y > HotDoggPos.y)
			m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::LEFT);
		// 3rd quadrant
		else if (closestPos.x < HotDoggPos.x && closestPos.y <= HotDoggPos.y)
			m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::LEFT);

		// 4th quadrant
		else if (closestPos.x >= HotDoggPos.x && closestPos.y < HotDoggPos.y)
			m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::RIGHT);
	}
	else if (m_HotDogMovement->GetIsMovingHorizontally() && (m_HotDogMovement->GetIsMovingVertically() == false))
	{
		//Set Ladder state
		glm::vec2 vecToPlayer{ xDiff, yDiff };
		vecToPlayer = normalize(vecToPlayer);

		if (vecToPlayer.y > 0.5f)
			m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::UP);
		else if (vecToPlayer.y < -0.5f)
			m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::DOWN);
		else {
			//On same floor 
			//get random dir
			int randomIdx = (rand() % 2);
			if(randomIdx == 0)
				m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::UP);
			else
				m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::DOWN);
		}
	}
	else if ((m_HotDogMovement->GetIsMovingHorizontally() == false) && (m_HotDogMovement->GetIsMovingVertically() == false)) {
		//if stuck failsafe
		switch (m_HotDogMovement->GetVerticalDir())
		{
		case VerticalDirection::DOWN:
			m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::UP);
			break;
		case VerticalDirection::UP:
			m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::DOWN);
			break;
		default:
			break;
		}	switch (m_HotDogMovement->GetHorizonDir())
		{
		case HorizontalDirection::RIGHT:
			m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::LEFT);
			break;
		case HorizontalDirection::LEFT:
			m_HotDogMovement->SetNewHorizontalDirection(HorizontalDirection::RIGHT);
			break;
		default:
			break;
		}
	}
	

}

int dae::HotDoggBehaviourComponent::GetPlayerQuadrant()
{
	glm::vec2 closestPos;
	glm::vec3 HotDoggPos = GetAttachedGameObject()->GetTransform().GetPosition();
	float distance = FLT_MAX;
	//if no player return
	if (m_PlayerVec.size() == 0)
		return 0;
	//Find closest Player
	for (size_t i = 0; i < m_PlayerVec.size(); i++)
	{
		//Calculate distance with center point of player
		float xDiff = HotDoggPos.x - (m_PlayerVec[i]->m_ColliderRect.x + ((m_PlayerVec[i]->m_ColliderRect.width / 2.f)));
		float yDiff = HotDoggPos.y - (m_PlayerVec[i]->m_ColliderRect.y + (m_PlayerVec[i]->m_ColliderRect.height / 2.f));
		float currDistance = std::sqrt(xDiff * xDiff + yDiff * yDiff);
		if (currDistance < distance) {
			closestPos.x = m_PlayerVec[i]->m_ColliderRect.x + ((m_PlayerVec[i]->m_ColliderRect.width / 2.f));
			closestPos.y = m_PlayerVec[i]->m_ColliderRect.y + (m_PlayerVec[i]->m_ColliderRect.height / 2.f);
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

	return quad;
}

