#include "MiniginPCH.h"
#include "AIBehaviourComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "MovementComponent.h"
#include "DeltaTime.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "MathHelper.h"
#include "BaseComponent.h"
#include "EventType.h"
#include "BurgerEvents.h"

using namespace dae;

Burger::AIBehaviourComponent::AIBehaviourComponent(std::string tagToFollow, EnemyType type, int score)
	: m_TagToFollow{tagToFollow}, m_Type{ type }, m_Score{ score }
{

}

Burger::AIBehaviourComponent::~AIBehaviourComponent()
{
	if (m_CurrState != nullptr)
		delete m_CurrState;
}

void Burger::AIBehaviourComponent::Start()
{
	
	m_HotDogMovement = GetAttachedGameObject()->GetComponent<MovementComponent>();
	m_SpriteComponent = GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();


	//register self for collision events
	m_ColliderComponent = GetAttachedGameObject()->GetComponent<dae::BoxColliderComponent>();
	assert(m_ColliderComponent);

	ColliderCallbacks colBack;
	colBack.OverlapEnterFunc = std::bind(&AIBehaviourComponent::OnCollisionEnter, this, std::placeholders::_1);
	colBack.OverlopExitFunc = std::bind(&AIBehaviourComponent::OnCollisionExit, this, std::placeholders::_1);
	colBack.OverlapStayFunc = std::bind(&AIBehaviourComponent::OnCollisionStay, this, std::placeholders::_1);

	m_ColliderComponent->AddListener(colBack);

}

void Burger::AIBehaviourComponent::Render() const
{
	
}

void Burger::AIBehaviourComponent::Update()
{
	if(m_PlayerVec.size() == 0)
		m_PlayerVec = GetAttachedGameObject()->GetScene()->GetAllCollidersWithTag(m_TagToFollow);

	if (m_CurrState != nullptr) {
		AIState* newState = m_CurrState->UpdateState(*this);
		if (newState != nullptr)
		{
			m_CurrState->Exit(*this);
			delete m_CurrState;
			m_CurrState = newState;
			m_CurrState->Entry(*this);

		}
	}
	else {
		//First setup
		m_CurrState = new HorizontalState();
		m_CurrState->Entry(*this);
		m_IsSpawning = false;
	}
	m_IsOnLadder = false;
	m_IsOnFloor = false;


}

void Burger::AIBehaviourComponent::SetHorizontalDir(HorizontalDirection horizon)
{
	m_HotDogMovement->SetNewHorizontalDirection(horizon);

}

void Burger::AIBehaviourComponent::SetVerticalDir(VerticalDirection vertical)
{
	m_HotDogMovement->SetNewVerticalDirection(vertical);

}

glm::vec2 Burger::AIBehaviourComponent::GetClosestPlayerPos() const
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






void Burger::AIBehaviourComponent::OnCollisionStay(const std::shared_ptr<ColliderInfo> otherInfo)
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

void Burger::AIBehaviourComponent::OnCollisionEnter(const std::shared_ptr<ColliderInfo> otherInfo)
{
	if (otherInfo->tag == "Shot") {
		std::cout << "hit\n";
		m_CurrState->Exit(*this);
		delete m_CurrState;
		m_CurrState = new HitState();
		m_CurrState->Entry(*this);
	}
	if (otherInfo->tag == "Bun") {

		glm::vec2 topCheck;
		topCheck.x = m_ColliderComponent->GetColliderInfo().m_ColliderRect.x 
			+ (m_ColliderComponent->GetColliderInfo().m_ColliderRect.width / 2.f);
		topCheck.y = m_ColliderComponent->GetColliderInfo().m_ColliderRect.y;

		//Bun detection
		if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, topCheck)) {
			m_IsDeath = true;
			m_CurrState->Exit(*this);
			delete m_CurrState;
			m_CurrState = new DeathState();
			m_CurrState->Entry(*this);
			//Death State
		}


	}

}

void Burger::AIBehaviourComponent::OnCollisionExit(const std::shared_ptr<ColliderInfo> otherInfo)
{

}

void Burger::HorizontalState::Entry(AIBehaviourComponent& ai)
{
	ColliderInfo AiInfo = ai.m_ColliderComponent->GetColliderInfo();
	glm::vec2 searchPos = { AiInfo.m_ColliderRect.x + (ai.m_SpriteComponent->GetFLipState() ? 0.f
		: AiInfo.m_ColliderRect.width)
		, AiInfo.m_ColliderRect.y + AiInfo.m_ColliderRect.height };
	//Check bounds
	auto rightFloorHit = ai.GetAttachedGameObject()->GetScene()->SceneRectcast(AiInfo.m_ColliderRect
		, glm::vec2(1, 0), 50.f, "Floor", 1);
	auto leftFloorHit = ai.GetAttachedGameObject()->GetScene()->SceneRectcast(AiInfo.m_ColliderRect
		, glm::vec2(-1, 0), 50.f, "Floor", 1);

	if (rightFloorHit == nullptr && ai.m_IsSpawning == false) {
		std::cout << "Right floor hit\n";
		ai.SetHorizontalDir(HorizontalDirection::LEFT);
		ai.m_SpriteComponent->SetActiveAnimation("MoveSide");
		ai.m_SpriteComponent->SetFlipState(false);
	}
	if (leftFloorHit == nullptr && ai.m_IsSpawning == false) {
		std::cout << "left floor hit\n";
		ai.SetHorizontalDir(HorizontalDirection::RIGHT);
		ai.m_SpriteComponent->SetActiveAnimation("MoveSide");
		ai.m_SpriteComponent->SetFlipState(true);
	}


	if (ai.m_HotDogMovement->GetHorizonDir() == HorizontalDirection::NONE) {
		glm::vec2 pos = ai.GetClosestPlayerPos();
		float currPosx = ai.GetAttachedGameObject()->GetTransform().GetPosition().x;

		if (pos.x < (currPosx)) {
			ai.SetHorizontalDir(HorizontalDirection::LEFT);
			ai.m_SpriteComponent->SetActiveAnimation("MoveSide");
			ai.m_SpriteComponent->SetFlipState(false);
		}
		if (pos.x > (currPosx)) {
			//Floor in sight
			ai.SetHorizontalDir(HorizontalDirection::RIGHT);
			ai.m_SpriteComponent->SetActiveAnimation("MoveSide");
			ai.m_SpriteComponent->SetFlipState(true);

		}
	}


	
}

Burger::AIState* Burger::HorizontalState::UpdateState(AIBehaviourComponent& ai)
{
	if (ai.m_IsOnLadder && m_CurrentTime > m_MinExitTime) {
		m_CurrentTime = 0.f;
		if (MathHelper::RandomBool(0.65f))
			return new VerticalState();
		else
			return new HorizontalState();

	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
	}

	return nullptr;
}



void Burger::HorizontalState::Exit(AIBehaviourComponent& ai)
{
	ai.SetHorizontalDir(HorizontalDirection::NONE);


}

Burger::AIState* Burger::VerticalState::UpdateState(AIBehaviourComponent& ai)
{
	if (ai.m_IsOnFloor && m_CurrentTime > m_MinExitTime) {
		m_CurrentTime = 0.f;
		return new HorizontalState();
		
	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
	}
	return nullptr;

}

void Burger::VerticalState::Exit(AIBehaviourComponent& ai)
{
	ai.SetVerticalDir(VerticalDirection::NONE);
}


void Burger::VerticalState::Entry(AIBehaviourComponent& ai)
{
	ai.SetHorizontalDir(HorizontalDirection::NONE);

	float posY = ai.GetClosestPlayerPos().y;
	float currPosY = ai.GetAttachedGameObject()->GetTransform().GetPosition().y;
	ColliderInfo AiInfo = ai.m_ColliderComponent->GetColliderInfo();

	glm::vec2 searchPos = { AiInfo.m_ColliderRect.x + (ai.m_SpriteComponent->GetFLipState() ? 0.f
		: AiInfo.m_ColliderRect.width)
		, AiInfo.m_ColliderRect.y + AiInfo.m_ColliderRect.height };
	if (posY < (currPosY )) {
		//Check if floor goes further else go other dir
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(searchPos, glm::vec2(0, -1), 35.f, "Ladder", 1)
			|| ai.m_IsSpawning) {

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
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(searchPos, glm::vec2(0, 1),35.f, "Ladder", 1)
			|| ai.m_IsSpawning) {
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


void Burger::HitState::Entry(AIBehaviourComponent& ai)
{
	//Se sprite
	ai.m_SpriteComponent->SetActiveAnimation("Fried");
	ai.m_SpriteComponent->SetFlipState(false);

	//Disable enemy collider
	ai.m_ColliderComponent->DisableCollider();
}




//HIT
Burger::AIState* Burger::HitState::UpdateState(AIBehaviourComponent&)
{
	if (m_CurrentTime > m_MinExitTime) {
		std::cout << "Enemy hit\n";
		m_CurrentTime = 0.f;
		return new HorizontalState();
	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
		return nullptr;
	}

}



void Burger::HitState::Exit(AIBehaviourComponent& ai)
{
	ai.m_ColliderComponent->EnableCollider();
}

void Burger::DeathState::Entry(AIBehaviourComponent& ai)
{
	ai.m_SpriteComponent->SetActiveAnimation("Death");
}



//DEATH
Burger::AIState* Burger::DeathState::UpdateState(AIBehaviourComponent& ai)
{
	if (ai.m_SpriteComponent->IsActiveInFinalFrame()) {
		m_IsSpawning = true;
		//Notify death of enemy
		EnemyArgs eArgs;
		eArgs.type = ai.m_Type;
		eArgs.points = ai.m_Score;
		ai.notify(&ai, PepperEvent::ENEMY_DIED, &eArgs);
		ai.GetAttachedGameObject()->SetDestroyFlag(true);
	}
	return nullptr;
}

void Burger::DeathState::Exit(AIBehaviourComponent&)
{

}
