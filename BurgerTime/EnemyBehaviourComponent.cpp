#pragma warning(disable:4201)

#include "MiniginPCH.h"
#include "EnemyBehaviourComponent.h"
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
#include "BitMaskOperators.h"

template<>
struct enable_bitmask_operators<Burger::EnemyBehaviourComponent::EnemyState> {
	static const bool enable = true;
};


using namespace dae;

Burger::EnemyBehaviourComponent::EnemyBehaviourComponent(std::string tagToFollow, EnemyType type, int score, bool isPlayerControlled)
	: m_TagToFollow{tagToFollow}, m_Type{ type }, m_Score{ score }, m_IsPlayerControllerd{ isPlayerControlled }
{

}

Burger::EnemyBehaviourComponent::~EnemyBehaviourComponent()
{
	if (m_CurrState != nullptr)
		delete m_CurrState;
}

void Burger::EnemyBehaviourComponent::Start()
{
	
	m_MovementComponent = GetAttachedGameObject()->GetComponent<MovementComponent>();
	m_SpriteComponent = GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();


	//register self for collision events
	m_ColliderComponent = GetAttachedGameObject()->GetComponent<dae::BoxColliderComponent>();
	assert(m_ColliderComponent);

	ColliderCallbacks colBack;
	colBack.OverlapEnterFunc = std::bind(&EnemyBehaviourComponent::OnCollisionEnter, this, std::placeholders::_1);
	colBack.OverlapStayFunc = std::bind(&EnemyBehaviourComponent::OnCollisionStay, this, std::placeholders::_1);
	colBack.OverlopExitFunc = std::bind(&EnemyBehaviourComponent::OnCollisionExit, this, std::placeholders::_1);


	m_ColliderComponent->AddListener(colBack);

	m_PlayerVec = GetAttachedGameObject()->GetScene()->GetGameObjectsWithTag(m_TagToFollow);
}

void Burger::EnemyBehaviourComponent::Render() const
{
	
}

void Burger::EnemyBehaviourComponent::Update()
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
			m_MovementComponent->SetMovementCollisionCheckDisable(true);
			m_EnemyState &= ~(m_EnemyState & EnemyState::Spawning); //flip spawn bit

		}
		

	}
	UpdateSprite();

}
void Burger::EnemyBehaviourComponent::SetFallState(float velocity)
{
	if (IsEnemyMutable()) {
		if (m_CurrState != nullptr) {
			m_CurrState->Exit(*this);
		}
		delete m_CurrState;
		m_CurrState = new FallingState();
		m_CurrState->Entry(*this);
		m_EnemyState |= EnemyState::Falling;
		m_MovementComponent->SetNewVelocity(velocity);
	}
}

point Burger::EnemyBehaviourComponent::GetClosestPlayerPos() const
{
	point closestPos{};
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






bool Burger::EnemyBehaviourComponent::IsEnemyMutable() const
{
	//If death or falling enemy is inmutable
	EnemyState isDeathActive = m_EnemyState & EnemyState::Death;
	EnemyState isFallingActive = m_EnemyState & EnemyState::Falling;

	if (isDeathActive  == EnemyState::Death || isFallingActive == EnemyState::Falling) {
		return false;
	}
	return true;
}

void Burger::EnemyBehaviourComponent::UpdateSprite()
{


	//make death and victory state
	if (!IsEnemyMutable())
		return;
	Direction dir = m_MovementComponent->GetMovement();

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

void Burger::EnemyBehaviourComponent::OnCollisionStay(const std::shared_ptr<ColliderInfo> otherInfo)
{
	ColliderInfo aiColInfo = m_ColliderComponent->GetColliderInfo();
	glm::vec2 searchPos = { aiColInfo.m_ColliderRect.x + (m_SpriteComponent->GetFLipState() ? 0.f
		: aiColInfo.m_ColliderRect.width)
		, aiColInfo.m_ColliderRect.y + aiColInfo.m_ColliderRect.height };

	if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, searchPos)) {
		if (otherInfo->tag == "Ladder") {
			if (m_CurrState != nullptr && IsEnemyMutable()) {
				m_EnemyState |= EnemyState::Ladder; //set ladder flag
				return;
			}
		}
		if (otherInfo->tag == "Floor") {

			if (m_CurrState != nullptr && IsEnemyMutable()) {
				m_EnemyState |= EnemyState::Floor; //set floor flag
				return;
			}
		}

	}

}
void Burger::EnemyBehaviourComponent::OnCollisionExit(const std::shared_ptr<dae::ColliderInfo> otherInfo)
{
	if (otherInfo->tag == "Ladder") {
		EnemyState isEnemyLadder = m_EnemyState & EnemyState::Ladder;
		if(isEnemyLadder == EnemyState::Ladder)
			m_EnemyState &= ~(isEnemyLadder); //flip ladder bit
	}
	if (otherInfo->tag == "Floor") {
		EnemyState isEnemyFloor = m_EnemyState & EnemyState::Floor;
		if (isEnemyFloor == EnemyState::Floor)
			m_EnemyState &= ~(isEnemyFloor); //flip floor bit
	}
}
void Burger::EnemyBehaviourComponent::OnCollisionEnter(const std::shared_ptr<ColliderInfo> otherInfo)
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
			m_EnemyState |= EnemyState::Death;
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
		m_EnemyState |= EnemyState::Death;
		if (m_CurrState != nullptr) {
			m_CurrState->Exit(*this);
		}
		delete m_CurrState;
		m_CurrState = new DeathState();
		m_CurrState->Entry(*this);
	}

}




void Burger::EnemyBehaviourComponent::HorizontalState::Entry(EnemyBehaviourComponent& ai)
{
	ColliderInfo AiInfo = ai.m_ColliderComponent->GetColliderInfo();
	AiInfo.m_ColliderRect.width *= 1.2f;
	AiInfo.m_ColliderRect.height *= 1.2f;

	//Check bounds
	auto rightFloorHit = ai.GetAttachedGameObject()->GetScene()->SceneRectcast(AiInfo.m_ColliderRect
		, glm::vec2(1, 0), 50.f, "Floor", 1);
	auto leftFloorHit = ai.GetAttachedGameObject()->GetScene()->SceneRectcast(AiInfo.m_ColliderRect
		, glm::vec2(-1, 0), 50.f, "Floor", 1);

	EnemyState isSpawning = ai.m_EnemyState & EnemyState::Spawning;
	if (rightFloorHit == nullptr && isSpawning != EnemyState::Spawning) {
		ai.m_MovementComponent->SetNewDirection(Direction::LEFT);
		return;
	}
	if (leftFloorHit == nullptr && isSpawning != EnemyState::Spawning) {
		ai.m_MovementComponent->SetNewDirection(Direction::RIGHT);
		return;
	}

	if (ai.m_MovementComponent->GetDirection() == Direction::NONE || ai.m_Type == EnemyType::SPIKE) {
		point pos = ai.GetClosestPlayerPos();
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

Burger::EnemyBehaviourComponent::AIState* Burger::EnemyBehaviourComponent::HorizontalState::UpdateState(EnemyBehaviourComponent& ai)
{
	EnemyState isEnemyLadder = ai.m_EnemyState & EnemyState::Ladder;

	if (isEnemyLadder == EnemyState::Ladder && m_CurrentTime > m_MinExitTime) {
		//ai.m_EnemyState &= ~(ai.m_EnemyState & EnemyState::Floor); //flip bit
		//reset ladder bit
		m_CurrentTime = 0.f;
		if (MathHelper::RandomBool(0.65f))
			return new VerticalState();
		else {
			ai.m_EnemyState &= ~(isEnemyLadder); //flip ladder bit
			return new HorizontalState();
		}
	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
	}

	return nullptr;
}



void Burger::EnemyBehaviourComponent::HorizontalState::Exit(EnemyBehaviourComponent& )
{


}

Burger::EnemyBehaviourComponent::AIState* Burger::EnemyBehaviourComponent::VerticalState::UpdateState(EnemyBehaviourComponent& ai)
{
	EnemyState isEnemyFloor= ai.m_EnemyState & EnemyState::Floor;

	if (isEnemyFloor == EnemyState::Floor  && m_CurrentTime > m_MinExitTime) {
		//ai.m_EnemyState &= ~(ai.m_EnemyState & EnemyState::Ladder); //flip bit


		m_CurrentTime = 0.f;
		return new HorizontalState();
		
	}
	else {
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
	}
	return nullptr;

}

void Burger::EnemyBehaviourComponent::VerticalState::Exit(EnemyBehaviourComponent& ai)
{
	ai.m_MovementComponent->SetNewDirection(Direction::NONE);
}


void Burger::EnemyBehaviourComponent::VerticalState::Entry(EnemyBehaviourComponent& ai)
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
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(searchPos, glm::vec2(0, -1), 20.f, "Ladder", 1)) {
			ai.m_MovementComponent->SetNewDirection(Direction::UP);
			return;

		}
		else {
			ai.m_MovementComponent->SetNewDirection(Direction::DOWN);
		}
	}
	

	if (posY > (currPosY)) {
		//Check if floor goes further else go other dir
		if (ai.GetAttachedGameObject()->GetScene()->SceneRaycast(searchPos, glm::vec2(0, 1),20.f, "Ladder", 1)) {
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
void Burger::EnemyBehaviourComponent::HitState::Entry(EnemyBehaviourComponent& ai)
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
Burger::EnemyBehaviourComponent::AIState* Burger::EnemyBehaviourComponent::HitState::UpdateState(EnemyBehaviourComponent&)
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
void Burger::EnemyBehaviourComponent::HitState::Exit(EnemyBehaviourComponent& ai)
{
	ai.m_ColliderComponent->EnableCollider();
	ai.m_MovementComponent->SetChangeMovementDisable(false);

}
//DEATH
void Burger::EnemyBehaviourComponent::DeathState::Entry(EnemyBehaviourComponent& ai)
{
	//play fx
	ServiceLocator::GetSoundSystem().play("Resources/FX/EnemyDeath.mp3");
	ai.m_ColliderComponent->DisableCollider();
	ai.m_MovementComponent->SetNewDirection(Direction::NONE);
	ai.m_SpriteComponent->SetActiveAnimation("Death");
}
Burger::EnemyBehaviourComponent::AIState* Burger::EnemyBehaviourComponent::DeathState::UpdateState(EnemyBehaviourComponent& ai)
{
	if (ai.m_SpriteComponent->IsActiveInFinalFrame()) {
		//Notify death of enemy
		EnemyArgs eArgs;
		eArgs.type = ai.m_Type;
		eArgs.points = ai.m_Score;
		ai.notify(&ai, PepperEvent::ENEMY_DIED, &eArgs);
		ai.GetAttachedGameObject()->SetDestroyFlag(true);
	}
	return nullptr;
}

void Burger::EnemyBehaviourComponent::DeathState::Exit(EnemyBehaviourComponent& ai)
{
	ai.m_ColliderComponent->DisableCollider();
}
//FALLL
void Burger::EnemyBehaviourComponent::FallingState::Entry(EnemyBehaviourComponent& ai)
{

	ai.m_MovementComponent->SetNewDirection(Direction::DOWN);

	ai.m_MovementComponent->SetMovementCollisionCheckDisable(true);
	ai.m_MovementComponent->SetChangeMovementDisable(true);


	//Play fx
	ServiceLocator::GetSoundSystem().play("Resources/FX/EnemyDrop.mp3");
}

Burger::EnemyBehaviourComponent::AIState* Burger::EnemyBehaviourComponent::FallingState::UpdateState(EnemyBehaviourComponent& )
{
	return nullptr;
}

void Burger::EnemyBehaviourComponent::FallingState::Exit(EnemyBehaviourComponent& ai)
{
	ai.m_MovementComponent->SetChangeMovementDisable(false);

}
