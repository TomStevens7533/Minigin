#include "MiniginPCH.h"
#include "AIBehaviourComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "MovementComponent.h"
#include "Time.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "MathHelper.h"


dae::HorizontalState dae::AIState::m_HorizontalState;

dae::VerticalState dae::AIState::m_VerticalState;

dae::HitState dae::AIState::m_HitState;



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

	ColliderCallbacks colBack;
	colBack.OverlapEnterFunc = std::bind(&AIBehaviourComponent::OnCollisionEnter, this, std::placeholders::_1);
	colBack.OverlopExitFunc = std::bind(&AIBehaviourComponent::OnCollisionExit, this, std::placeholders::_1);
	colBack.OverlapStayFunc = std::bind(&AIBehaviourComponent::OnCollisionStay, this, std::placeholders::_1);

	m_ColliderComponent->AddListener(colBack);

}

void dae::AIBehaviourComponent::Render() const
{
	
}

void dae::AIBehaviourComponent::Update()
{
	if (m_CurrState != nullptr) {
		AIState* newState = m_CurrState->UpdateState(*this);
		if (newState != nullptr)
		{
			m_CurrState->Exit(*this);
			m_CurrState = newState;
			m_CurrState->Entry(*this);

		}
	}
	else {
		//First setup
		m_CurrState = &AIState::m_HorizontalState;
		m_CurrState->Entry(*this);
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






void dae::AIBehaviourComponent::OnCollisionStay(const std::shared_ptr<ColliderInfo> otherInfo)
{
	ColliderInfo aiColInfo = m_ColliderComponent->GetColliderInfo();
	glm::vec2 searchPos = { aiColInfo.m_ColliderRect.x + (m_SpriteComponent->GetFLipState() ? 0.f
		: aiColInfo.m_ColliderRect.width)
		, aiColInfo.m_ColliderRect.y + aiColInfo.m_ColliderRect.height };

	if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, searchPos)) {
		if (otherInfo->tag == "Ladder") {
			if (m_CurrState != nullptr) {
				m_IsOnLadder = true;
			}



		}
		if (otherInfo->tag == "Floor") {

			if (m_CurrState != nullptr) {
				m_IsOnFloor = true;
			}
		}

	}

}

void dae::AIBehaviourComponent::OnCollisionEnter(const std::shared_ptr<ColliderInfo> otherInfo)
{
	if (otherInfo->tag == "Shot") {
		std::cout << "hit\n";
		m_CurrState->Exit(*this);
		m_CurrState = &AIState::m_HitState;
		m_CurrState->Entry(*this);
	}

}

void dae::AIBehaviourComponent::OnCollisionExit(const std::shared_ptr<ColliderInfo> otherInfo)
{

}

void dae::HorizontalState::Entry(AIBehaviourComponent& ai)
{

	glm::vec2 pos = ai.GetClosestPlayerPos();
	float currPosx = ai.GetAttachedGameObject()->GetTransform().GetPosition().x;
	ColliderInfo AiInfo = ai.m_ColliderComponent->GetColliderInfo();

	glm::vec2 searchPos = { AiInfo.m_ColliderRect.x + (ai.m_SpriteComponent->GetFLipState() ? 0.f
		: AiInfo.m_ColliderRect.width)
		, AiInfo.m_ColliderRect.y + AiInfo.m_ColliderRect.height };

	if (pos.x < (currPosx)) {
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(searchPos
			, glm::vec2(-1, 0), 35.f, "Floor", 1)) {
			ai.SetHorizontalDir(HorizontalDirection::LEFT);
			ai.m_SpriteComponent->SetActiveAnimation("MoveSide");
			ai.m_SpriteComponent->SetFlipState(false);
		}
		else {
			ai.SetHorizontalDir(HorizontalDirection::RIGHT);
			ai.m_SpriteComponent->SetActiveAnimation("MoveSide");
			ai.m_SpriteComponent->SetFlipState(true);
		}

		//Set anim
		
		//Floor in sight
	}
	if (pos.x > (currPosx)) {
		//Floor in sight
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(searchPos
			, glm::vec2(1, 0), 35.f, "Floor", 1)) {

			ai.SetHorizontalDir(HorizontalDirection::RIGHT);
			ai.m_SpriteComponent->SetActiveAnimation("MoveSide");
			ai.m_SpriteComponent->SetFlipState(true);
		}
		else {
			ai.SetHorizontalDir(HorizontalDirection::LEFT);
			ai.m_SpriteComponent->SetActiveAnimation("MoveSide");
			ai.m_SpriteComponent->SetFlipState(false);
		}
		
	}
}

dae::AIState* dae::HorizontalState::UpdateState(AIBehaviourComponent& ai)
{
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
	ColliderInfo AiInfo = ai.m_ColliderComponent->GetColliderInfo();

	glm::vec2 searchPos = { AiInfo.m_ColliderRect.x + (ai.m_SpriteComponent->GetFLipState() ? 0.f
		: AiInfo.m_ColliderRect.width)
		, AiInfo.m_ColliderRect.y + AiInfo.m_ColliderRect.height };
	if (posY < (currPosY )) {
		//Check if floor goes further else go other dir
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(searchPos, glm::vec2(0, -1), 35.f, "Ladder", 1)) {
			ai.SetVerticalDir(VerticalDirection::UP);
			ai.m_SpriteComponent->SetActiveAnimation("MoveBackwards");
			ai.m_SpriteComponent->SetFlipState(false);
			return;
		}
		else {
			ai.m_SpriteComponent->SetActiveAnimation("MoveForward");
			ai.m_SpriteComponent->SetFlipState(false);
			ai.SetVerticalDir(VerticalDirection::DOWN);

		}
	}
	

	if (posY > (currPosY)) {
		//Check if floor goes further else go other dir
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(searchPos, glm::vec2(0, 1),35.f, "Ladder", 1)) {
			//Floor in sight
				ai.SetVerticalDir(VerticalDirection::DOWN);
				ai.m_SpriteComponent->SetActiveAnimation("MoveForward");
				ai.m_SpriteComponent->SetFlipState(false);
				return;
			}
			else {
				ai.m_SpriteComponent->SetActiveAnimation("MoveBackwards");
				ai.m_SpriteComponent->SetFlipState(false);
				ai.SetVerticalDir(VerticalDirection::UP);
				return;

			}
	}


}


void dae::HitState::Entry(AIBehaviourComponent& ai)
{
	//Se sprite
	ai.m_SpriteComponent->SetActiveAnimation("Fried");
	ai.m_SpriteComponent->SetFlipState(false);
}

dae::AIState* dae::HitState::UpdateState(AIBehaviourComponent&)
{
	if (m_CurrentTime > m_MinExitTime) {
		std::cout << "Enemy hit\n";
		m_CurrentTime = 0.f;
		return &AIState::m_HorizontalState;
	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
		return nullptr;
	}

}
