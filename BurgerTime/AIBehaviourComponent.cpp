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
#include "ServiceLocator.h"


using namespace dae;

Burger::AIBehaviourComponent::AIBehaviourComponent(std::string tagToFollow, EnemyType type, int score, bool isPlayerControlled)
	: m_TagToFollow{tagToFollow}, m_Type{ type }, m_Score{ score }, m_IsPlayerControllerd{ isPlayerControlled }
{

}

Burger::AIBehaviourComponent::~AIBehaviourComponent()
{
	if (m_CurrState != nullptr)
		delete m_CurrState;
}

void Burger::AIBehaviourComponent::Start()
{
	
	m_MovementComponent = GetAttachedGameObject()->GetComponent<MovementComponent>();
	m_SpriteComponent = GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();


	//register self for collision events
	m_ColliderComponent = GetAttachedGameObject()->GetComponent<dae::BoxColliderComponent>();
	assert(m_ColliderComponent);

	ColliderCallbacks colBack;
	colBack.OverlapEnterFunc = std::bind(&AIBehaviourComponent::OnCollisionEnter, this, std::placeholders::_1);
	colBack.OverlopExitFunc = std::bind(&AIBehaviourComponent::OnCollisionExit, this, std::placeholders::_1);
	colBack.OverlapStayFunc = std::bind(&AIBehaviourComponent::OnCollisionStay, this, std::placeholders::_1);

	m_ColliderComponent->AddListener(colBack);

	m_PlayerVec = GetAttachedGameObject()->GetScene()->GetGameObjectsWithTag(m_TagToFollow);
}

void Burger::AIBehaviourComponent::Render() const
{
	
}

void Burger::AIBehaviourComponent::Update()
{
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
		if (m_IsPlayerControllerd == false) {
			m_MovementComponent->SetMovementCollisionCheckDisable(false);
			m_CurrState = new HorizontalState();
			m_CurrState->Entry(*this);
			m_IsSpawning = false;
			m_MovementComponent->SetMovementCollisionCheckDisable(true);
		}
		

	}
	m_IsOnLadder = false;
	m_IsOnFloor = false;
	UpdateSprite();

}
void Burger::AIBehaviourComponent::SetFallState(float velocity)
{
	if (!m_IsFalling) {
		if (m_CurrState != nullptr) {
			m_CurrState->Exit(*this);
		}
		delete m_CurrState;
		m_CurrState = new FallingState();
		m_CurrState->Entry(*this);
		m_IsFalling = true;


		m_MovementComponent->SetNewVelocity(velocity);
		

	}
}

glm::vec2 Burger::AIBehaviourComponent::GetClosestPlayerPos() const
{
	glm::vec2 closestPos;
	glm::vec3 HotDoggPos = GetAttachedGameObject()->GetTransform().GetPosition();
	float distance = FLT_MAX;
	assert(m_PlayerVec.size() != 0);

	//Find closest Player
	for (size_t i = 0; i < m_PlayerVec.size(); i++)
	{
		glm::vec3 playerPos = m_PlayerVec[i]->GetTransform().GetPosition();
		//Calculate distance with center point of player
		float xDiff = HotDoggPos.x - (playerPos.x);
		float yDiff = HotDoggPos.y - (playerPos.y);
		float currDistance = std::sqrt(xDiff * xDiff + yDiff * yDiff);
		if (currDistance < distance) {
			closestPos.x = playerPos.x;
			closestPos.y = playerPos.y;
			currDistance = distance;
		}
	}
	return closestPos;
}






void Burger::AIBehaviourComponent::UpdateSprite()
{

	Direction dir = m_MovementComponent->GetMovement();

	//make death and victory state
	if (m_IsDeath)
		return;

	switch (dir)
	{
	case Direction::LEFT:
		m_SpriteComponent->SetActiveAnimation("MoveSide");
		m_SpriteComponent->SetFlipState(false);
		break;
	case Direction::RIGHT:
		m_SpriteComponent->SetActiveAnimation("MoveSide");
		m_SpriteComponent->SetFlipState(true);
		break;
	case Direction::UP:
		m_SpriteComponent->SetActiveAnimation("MoveBackwards");
		m_SpriteComponent->SetFlipState(false);
		break;
	case Direction::DOWN:
		m_SpriteComponent->SetActiveAnimation("MoveForward");
		m_SpriteComponent->SetFlipState(false);
		break;
	default:
		break;
	}
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
		if (m_CurrState != nullptr) {
			m_CurrState->Exit(*this);
		}
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
			if (m_CurrState != nullptr) {
				m_CurrState->Exit(*this);
			}
			delete m_CurrState;
			m_CurrState = new DeathState();
			m_CurrState->Entry(*this);
			//Death State
		}
	}
	else if (otherInfo->tag == "BunEnd") {
		m_IsDeath = true;
		if (m_CurrState != nullptr) {
			m_CurrState->Exit(*this);
		}
		delete m_CurrState;
		m_CurrState = new DeathState();
		m_CurrState->Entry(*this);
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
		ai.m_MovementComponent->SetNewDirection(Direction::LEFT);
		return;
	}
	if (leftFloorHit == nullptr && ai.m_IsSpawning == false) {
		ai.m_MovementComponent->SetNewDirection(Direction::RIGHT);
		return;
	}


	if (ai.m_MovementComponent->GetDirection() == Direction::NONE) {
		glm::vec2 pos = ai.GetClosestPlayerPos();
		float currPosx = ai.GetAttachedGameObject()->GetTransform().GetPosition().x;

		if (pos.x < (currPosx)) {
			ai.m_MovementComponent->SetNewDirection(Direction::LEFT);
		}
		if (pos.x > (currPosx)) {
			//Floor in sight
			ai.m_MovementComponent->SetNewDirection(Direction::RIGHT);

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
	else if (ai.m_Type == EnemyType::SPIKE && ai.m_IsOnFloor && m_CurrentTime > m_MinExitTime) { //Flipping of mr pickle
		if (MathHelper::RandomBool(0.1f)) {
			m_CurrentTime = 0.f;
			return new HorizontalState();
		}
	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
	}

	return nullptr;
}



void Burger::HorizontalState::Exit(AIBehaviourComponent& ai)
{


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
	ai.m_MovementComponent->SetNewDirection(Direction::NONE);
}


void Burger::VerticalState::Entry(AIBehaviourComponent& ai)
{
	ai.m_MovementComponent->SetNewDirection(Direction::NONE);


	float posY = ai.GetClosestPlayerPos().y;
	float currPosY = ai.GetAttachedGameObject()->GetTransform().GetPosition().y;
	ColliderInfo AiInfo = ai.m_ColliderComponent->GetColliderInfo();

	glm::vec2 searchPos = { AiInfo.m_ColliderRect.x + (ai.m_SpriteComponent->GetFLipState() ? 0.f
		: AiInfo.m_ColliderRect.width)
		, AiInfo.m_ColliderRect.y + AiInfo.m_ColliderRect.height };
	if (posY < (currPosY )) {
		//Check if floor goes further else go other dir
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(searchPos, glm::vec2(0, -1), 20.f, "Ladder", 1)
			|| ai.m_IsSpawning) {
			ai.m_MovementComponent->SetNewDirection(Direction::UP);
			return;

		}
		else {
			ai.m_MovementComponent->SetNewDirection(Direction::DOWN);
		}
	}
	

	if (posY > (currPosY)) {
		//Check if floor goes further else go other dir
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(searchPos, glm::vec2(0, 1),20.f, "Ladder", 1)
			|| ai.m_IsSpawning) {
			//Floor in sight
				ai.m_MovementComponent->SetNewDirection(Direction::DOWN);
				return;
			}
			else {
				ai.m_MovementComponent->SetNewDirection(Direction::UP);
				return;

			}
	}


}

//HIT
void Burger::HitState::Entry(AIBehaviourComponent& ai)
{
	//Se sprite
	ai.m_SpriteComponent->SetActiveAnimation("Fried");
	ai.m_SpriteComponent->SetFlipState(false);
	ai.m_MovementComponent->SetNewDirection(Direction::NONE);


	//play fx
	ServiceLocator::GetSoundSystem().play("Resources/FX/EnemyStun.mp3");
	

	//Disable enemy collider
	ai.m_ColliderComponent->DisableCollider();
	ai.m_MovementComponent->SetNewDirection(Direction::NONE);
	ai.m_MovementComponent->SetChangeMovementDisable(true);
}
Burger::AIState* Burger::HitState::UpdateState(AIBehaviourComponent&)
{
	if (m_CurrentTime > m_MinExitTime) {
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
	ai.m_MovementComponent->SetChangeMovementDisable(false);

}
//DEATH
void Burger::DeathState::Entry(AIBehaviourComponent& ai)
{
	//play fx
	ServiceLocator::GetSoundSystem().play("Resources/FX/EnemyDeath.mp3");
	ai.m_ColliderComponent->DisableCollider();
	ai.m_MovementComponent->SetNewDirection(Direction::NONE);
	ai.m_SpriteComponent->SetActiveAnimation("Death");
}
Burger::AIState* Burger::DeathState::UpdateState(AIBehaviourComponent& ai)
{
	if (ai.m_SpriteComponent->IsActiveInFinalFrame()) {
		std::cout << "death\n";
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

void Burger::DeathState::Exit(AIBehaviourComponent& ai)
{
	ai.m_ColliderComponent->DisableCollider();
}
//FALLL
void Burger::FallingState::Entry(AIBehaviourComponent& ai)
{

	ai.m_MovementComponent->SetNewDirection(Direction::DOWN);

	ai.m_MovementComponent->SetMovementCollisionCheckDisable(true);
	ai.m_MovementComponent->SetChangeMovementDisable(true);


	//Play fx
	ServiceLocator::GetSoundSystem().play("Resources/FX/EnemyDrop.mp3");
}

Burger::AIState* Burger::FallingState::UpdateState(AIBehaviourComponent& ai)
{
	return nullptr;
}

void Burger::FallingState::Exit(AIBehaviourComponent& ai)
{
	ai.m_MovementComponent->SetChangeMovementDisable(false);

}
