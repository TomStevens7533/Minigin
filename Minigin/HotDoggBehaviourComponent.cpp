#include "MiniginPCH.h"
#include "HotDoggBehaviourComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "MovementComponent.h"
#include "Time.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "MathHelper.h"

dae::HorizontalState dae::AIState::m_HorizontalState;

dae::VerticalState dae::AIState::m_VerticalState;

dae::IdleState dae::AIState::m_IdleState;



dae::AIBehaviourComponent::AIBehaviourComponent(std::string tagToFollow) : m_TagToFollow{tagToFollow}
{

}

void dae::AIBehaviourComponent::Start()
{
	m_PlayerVec = GetAttachedGameObject()->GetScene()->GetAllCollidersWithTag(m_TagToFollow);
	m_HotDogMovement = GetAttachedGameObject()->GetComponent<MovementComponent>();
	m_SpriteComponent = GetAttachedGameObject()->GetComponent<SpriteComponent>();


	//register self for collision events
	m_ColliderComponent = GetAttachedGameObject()->GetComponent<BoxColliderComponent>();
	assert(m_ColliderComponent);

	if (m_ColliderComponent) {
		m_ColliderComponent->addObserver(this);
	}
	m_CurrState = &AIState::m_HorizontalState;
	m_CurrState->Entry(*this);
}

void dae::AIBehaviourComponent::Render() const
{
	
}

void dae::AIBehaviourComponent::Update()
{
	/*if (m_CurrState == nullptr) {
		m_CurrState = &dae::AIState::m_HorizontalState;
		m_CurrState->Entry(*this);
	}
	if (newState != nullptr) {
		m_CurrState->Exit(*this);
		m_CurrState = newState;
		m_CurrState->Entry(*this);
	}*/

	if (m_CurrState != nullptr) {
		AIState* newState = m_CurrState->UpdateState(*this);
		if (newState != nullptr)
		{
			m_CurrState->Exit(*this);
			m_CurrState = newState;
			m_CurrState->Entry(*this);

		}
	}
	m_IsOnLadder = false;
	m_IsOnFloor = false;


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
			closestPos.y = m_PlayerVec[i]->m_ColliderRect.y + (m_PlayerVec[i]->m_ColliderRect.height);
			currDistance = distance;
		}
	}
	return closestPos;
}






void dae::AIBehaviourComponent::onNotify(const BaseComponent* , int eventType, EventArgs* args)
{
	ColliderInfo colInfo;
	ColliderInfo AiInfo = m_ColliderComponent->GetColliderInfo();
	CollisionArgs* colArgs;
	glm::vec2 searchPos;
	switch (eventType)
	{
	case EventType::OnCollisionStay:
		//Change to dynamic safety check
		colArgs = static_cast<CollisionArgs*>(args);
		colInfo = colArgs->info;
		searchPos = { AiInfo.m_ColliderRect.x + AiInfo.m_ColliderRect.width
			, AiInfo.m_ColliderRect.y + AiInfo.m_ColliderRect.height };
		if (MathHelper::IsPointInRect(colInfo.m_ColliderRect, searchPos)) {
			if (colInfo.tag == "Ladder") {
				if (m_CurrState != nullptr) {
					m_IsOnLadder = true;
				}
			


			}
			if (colInfo.tag == "Floor") {

				if (m_CurrState != nullptr) {
					m_IsOnFloor = true;
				}
			}
						
		}

		
	default:
		break;
	}
}

void dae::HorizontalState::Entry(AIBehaviourComponent& ai)
{

	glm::vec2 pos = ai.GetClosestPlayerPos();
	float currPosx = ai.GetAttachedGameObject()->GetTransform().GetPosition().x;
	if (pos.x < (currPosx)) {
		//if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(ai.GetMovementComponent()->GetCenterPos()
		//	, glm::vec2(-1, 0), 35.f, "Floor", 1)) {
			ai.SetHorizontalDir(HorizontalDirection::LEFT);
			ai.GetSpriteComponent()->SetActiveAnimation("MoveSide");
			ai.GetSpriteComponent()->SetFlipState(false);
	/*	}
		else {
			ai.SetHorizontalDir(HorizontalDirection::RIGHT);
			ai.GetSpriteComponent()->SetActiveAnimation("MoveSide");
			ai.GetSpriteComponent()->SetFlipState(true);
		}*/

		//Set anim
		
		//Floor in sight
	}
	if (pos.x > (currPosx)) {
		//Floor in sight
	/*	if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(ai.GetMovementComponent()->GetCenterPos()
			, glm::vec2(1, 0), 35.f, "Floor", 1)) {*/

			ai.SetHorizontalDir(HorizontalDirection::RIGHT);
			ai.GetSpriteComponent()->SetActiveAnimation("MoveSide");
			ai.GetSpriteComponent()->SetFlipState(true);
		
	}
}

dae::AIState* dae::HorizontalState::UpdateState(AIBehaviourComponent& ai)
{
	//auto it = ai.GetAttachedGameObject()
	//	->GetScene()->IsPointInCollider(ai.GetAttachedGameObject()->GetTransform().GetPosition(), "Shot");
	//if (it) {
	//	return &AIState::m_IdleState;
	//}

	//if notmoving horizontally switch
	if (ai.m_IsOnLadder && m_CurrentTime > m_MinExitTime) {
		m_CurrentTime = 0.f;
		return &AIState::m_VerticalState;
	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
	}



	return nullptr;
}



dae::AIState* dae::VerticalState::UpdateState(AIBehaviourComponent& ai)
{

	/*auto it = ai.GetAttachedGameObject()
		->GetScene()->IsPointInCollider(ai.GetAttachedGameObject()->GetTransform().GetPosition(), "Shot");
	if (it) {
		return &AIState::m_IdleState;
	}
	*/
	if (ai.m_IsOnFloor && m_CurrentTime > m_MinExitTime) {
		m_CurrentTime = 0.f;
		return &AIState::m_HorizontalState;
	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
	}
	return nullptr;

}

void dae::VerticalState::Exit(AIBehaviourComponent& ai)
{
	ai.SetVerticalDir(VerticalDirection::NONE);
}
void dae::HorizontalState::Exit(AIBehaviourComponent& ai)
{
	ai.SetHorizontalDir(HorizontalDirection::NONE);
}



void dae::VerticalState::Entry(AIBehaviourComponent& ai)
{

	float posY = ai.GetClosestPlayerPos().y;
	float currPosY = ai.GetAttachedGameObject()->GetTransform().GetPosition().y;
	if (posY < (currPosY )) {
		/*if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(ai.GetMovementComponent()->GetCenterPos(), glm::vec2(0, -1), 35.f, "Ladder", 1)) {
			Floor in sight*/
			ai.SetVerticalDir(VerticalDirection::UP);
			ai.GetSpriteComponent()->SetActiveAnimation("MoveBackwards");
			ai.GetSpriteComponent()->SetFlipState(false);
			return;
		//}
		//else {
		//	ai.GetSpriteComponent()->SetActiveAnimation("MoveForward");
		//	ai.GetSpriteComponent()->SetFlipState(false);
		//	ai.SetVerticalDir(VerticalDirection::DOWN);

		//}
	}
	

	if (posY > (currPosY)) {
		//if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(ai.GetMovementComponent()->GetCenterPos(), glm::vec2(0, 1),35.f, "Ladder", 1)) {
			//Floor in sight
			ai.SetVerticalDir(VerticalDirection::DOWN);
			ai.GetSpriteComponent()->SetActiveAnimation("MoveForward");
			ai.GetSpriteComponent()->SetFlipState(false);
			return;
			/*	}
				else {
					ai.GetSpriteComponent()->SetActiveAnimation("MoveBackwards");
					ai.GetSpriteComponent()->SetFlipState(false);
					ai.SetVerticalDir(VerticalDirection::UP);

				}*/
	}


}


dae::AIState* dae::IdleState::UpdateState(AIBehaviourComponent&)
{
	std::cout << "Enemy hit\n";
	return &AIState::m_HorizontalState;
}
