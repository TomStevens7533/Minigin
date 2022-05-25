#include "MiniginPCH.h"
#include "HotDoggBehaviourComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "MovementComponent.h"
#include "Time.h"

dae::HorizontalState dae::AIState::m_HorizontalState;

dae::VerticalState dae::AIState::m_VerticalState;


dae::AIBehaviourComponent::AIBehaviourComponent(std::string tagToFollow) : m_TagToFollow{tagToFollow}
{
}

void dae::AIBehaviourComponent::Start()
{
	m_PlayerVec = GetAttachedGameObject()->GetScene()->GetAllCollidersWithTag(m_TagToFollow);
	m_HotDogMovement = GetAttachedGameObject()->GetComponent<MovementComponent>();
	m_HotDogMovement->SetNewVerticalDirection(VerticalDirection::DOWN);

	m_CurrState = &dae::AIState::m_HorizontalState;
	m_CurrState->Entry(*this);

}

void dae::AIBehaviourComponent::Update()
{
	
	AIState* newState = m_CurrState->UpdateState(*this);
	if (newState != nullptr) {
		m_CurrState = newState;
		m_CurrState->Entry(*this);
	}

}

void dae::AIBehaviourComponent::SetHorizontalDir(HorizontalDirection horizon)
{
	m_HotDogMovement->SetNewHorizontalDirection(horizon);

}

void dae::AIBehaviourComponent::SetVerticalDir(VerticalDirection vertical)
{
	m_HotDogMovement->SetNewVerticalDirection(vertical);

}

glm::vec2 dae::AIBehaviourComponent::GetClosestPlayerPos() const
{
	glm::vec2 closestPos;
	glm::vec3 HotDoggPos = GetAttachedGameObject()->GetTransform().GetPosition();
	float distance = FLT_MAX;
	//if no player return
	assert(m_PlayerVec.size() != 0);

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
	return closestPos;
}






void dae::HorizontalState::Entry(AIBehaviourComponent& ai)
{

	glm::vec2 pos = ai.GetClosestPlayerPos();
	float currPosx = ai.GetAttachedGameObject()->GetTransform().GetPosition().x;
	if (pos.x < (currPosx)) {
		ai.SetHorizontalDir(HorizontalDirection::LEFT);
		//Floor in sight
	}
	if (pos.x > (currPosx)) {
		//Floor in sight
		ai.SetHorizontalDir(HorizontalDirection::RIGHT);
	}
}

dae::AIState* dae::HorizontalState::UpdateState(AIBehaviourComponent& ai)
{
	//if notmoving horizontally switch
	if (ai.GetMovementComponent()->CanMoveVertically() && m_CurrentTime > m_MinExitTime) {
		m_CurrentTime = 0.f;
		return &AIState::m_VerticalState;
	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
	}

	return nullptr;
}



void dae::VerticalState::Entry(AIBehaviourComponent& ai)
{

	float posY = ai.GetClosestPlayerPos().y;
	float currPosY = ai.GetAttachedGameObject()->GetTransform().GetPosition().y;
	if (posY < (currPosY )) {
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(ai.GetMovementComponent()->GetCenterPos(), glm::vec2(0, -1), 50.f, "Ladder", 1)) {
			//Floor in sight
			ai.SetVerticalDir(VerticalDirection::UP);
			return;
		}
		else
			ai.SetVerticalDir(VerticalDirection::DOWN);
	}
	

	if (posY > (currPosY)) {
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(ai.GetMovementComponent()->GetCenterPos(), glm::vec2(0, 1), 50.f, "Ladder", 1)) {
			//Floor in sight
			ai.SetVerticalDir(VerticalDirection::DOWN);
			return;
		}
		else
			ai.SetVerticalDir(VerticalDirection::UP);
	}


}

dae::AIState* dae::VerticalState::UpdateState(AIBehaviourComponent& ai)
{

	if (ai.GetMovementComponent()->GetIsMovingHorizontally() && m_CurrentTime > m_MinExitTime) {
		m_CurrentTime = 0.f;
		return &AIState::m_HorizontalState;
	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
	}
	return nullptr;

}
