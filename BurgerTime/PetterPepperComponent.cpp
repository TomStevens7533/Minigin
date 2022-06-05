#include "MiniginPCH.h"
#include "PetterPepperComponent.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Command.cpp"
#include "AttackComponent.h"
#include "BoxColliderComponent.h"
#include "structs.h"
#include "MathHelper.h"
#include "MovementComponent.h"
#include "EventType.h"
#include "DeltaTime.h"
#include "BurgerTimeManager.h"
#include "ServiceLocator.h"

namespace Burger {

	bool PetterPepperComponent::m_IsFinished = false;

	int PetterPepperComponent::m_PepperAmountInGame = 0;



	PetterPepperComponent::~PetterPepperComponent()
	{
		GameManager::GetInstance().removeObserver(this);

	}

	void PetterPepperComponent::Start()
	{
		auto inputComp = GetAttachedGameObject()->GetComponent<dae::InputComponent>();
		m_SpriteComponent = GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();
		auto CollComp = GetAttachedGameObject()->GetComponent<dae::BoxColliderComponent>();

		m_MovementComponent = GetAttachedGameObject()->GetComponent<MovementComponent>();
		auto attackComp = GetAttachedGameObject()->GetComponent<AttackComponent>();

		GameManager::GetInstance().addObserver(this);
		if (m_PepperAmountInGame % 2 == 1)
		{
			//ARROWS
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_BUTTON_EAST, 13, new AttackCommand(attackComp), dae::KeyState::PRESSED);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_LEFT, 37, new MoveLeftEnterCommand(m_MovementComponent), dae::KeyState::DOWN);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveRightEnterCommand(m_MovementComponent), dae::KeyState::DOWN);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_UP, 38, new MoveUpEnterCommand(m_MovementComponent), dae::KeyState::DOWN);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_DOWN, 40, new MoveDownEnterCommand(m_MovementComponent), dae::KeyState::DOWN);


			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_LEFT, 37, new MoveLeftExitCommand(m_MovementComponent), dae::KeyState::RELEASED);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveRightExitCommand(m_MovementComponent), dae::KeyState::RELEASED);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_UP, 38, new MoveUpExitCommand(m_MovementComponent), dae::KeyState::RELEASED);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_DOWN, 40, new MoveDownExitCommand(m_MovementComponent), dae::KeyState::RELEASED);
		}
		else {
			//WASD
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_BUTTON_EAST, 'Q', new AttackCommand(attackComp), dae::KeyState::PRESSED);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_LEFT, 'A', new MoveLeftEnterCommand(m_MovementComponent), dae::KeyState::DOWN);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_RIGHT, 'D', new MoveRightEnterCommand(m_MovementComponent), dae::KeyState::DOWN);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_UP, 'W', new MoveUpEnterCommand(m_MovementComponent), dae::KeyState::DOWN);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_DOWN, 'S', new MoveDownEnterCommand(m_MovementComponent), dae::KeyState::DOWN);


			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_LEFT, 'A', new MoveLeftExitCommand(m_MovementComponent), dae::KeyState::RELEASED);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_RIGHT, 'D', new MoveRightExitCommand(m_MovementComponent), dae::KeyState::RELEASED);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_UP, 'W', new MoveUpExitCommand(m_MovementComponent), dae::KeyState::RELEASED);
			inputComp->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_DOWN, 'S', new MoveDownExitCommand(m_MovementComponent), dae::KeyState::RELEASED);
		}


		++m_PepperAmountInGame;

		//Adds itself as observor fol collision events
		if (CollComp) {
			dae::ColliderCallbacks colBack;
			colBack.OverlapEnterFunc = std::bind(&PetterPepperComponent::OnCollisionEnter, this, std::placeholders::_1);
			colBack.OverlopExitFunc = std::bind(&PetterPepperComponent::OnCollisionExit, this, std::placeholders::_1);
			colBack.OverlapStayFunc = std::bind(&PetterPepperComponent::OnCollisionStay, this, std::placeholders::_1);

			CollComp->AddListener(colBack);
		}

	}

	void PetterPepperComponent::Update()
	{
		if (m_IsVictory) {

			if (m_CurrentVictroyDance < m_MaxVictoryDance)
				m_CurrentVictroyDance += dae::Time::GetInstance().GetDeltaTime();
			else {
				if (m_IsFinished == false) { //make sure it does not get called multiple times in coop
					m_PepperAmountInGame = 0;
					m_CurrentVictroyDance = 0.f;
					GameManager::GetInstance().GoToNextLevel();
				}
			}
		}
		UpdateSprite();
	}

	void PetterPepperComponent::FixedUpdate()
	{


		if (m_IsHit && m_SpriteComponent->IsActiveInFinalFrame()) {

			m_PepperAmountInGame = 0;
			notify(this, PepperEvent::HEALTH_DECREASE);
			m_IsHit = false;
		}
	}

	void PetterPepperComponent::OnCollisionStay(const std::shared_ptr<dae::ColliderInfo> otherInfo)
	{



	}

	void PetterPepperComponent::OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo)
	{
		//Check enemy hit
		if (otherInfo->tag == "Enemy" && m_IsVictory == false) {
			m_IsHit = true;
			m_SpriteComponent->SetActiveAnimation("Death");
			m_SpriteComponent->SetFlipState(false);
			auto moveComp = GetAttachedGameObject()->GetComponent<MovementComponent>();
			moveComp->SetNewDirection(Direction::NONE);
			moveComp->SetChangeMovementDisable(true);


		}
	}

	void PetterPepperComponent::OnCollisionExit(const std::shared_ptr<dae::ColliderInfo> otherInfo)
	{

	}

	void PetterPepperComponent::onNotify(const BaseComponent* entity, int event, dae::EventArgs* args /*= nullptr*/)
	{
		switch (event)
		{
		case Burger::PepperEvent::LEVEL_COMPLETE:
			//Start dance
			m_SpriteComponent->SetActiveAnimation("Victory");
			ServiceLocator::GetSoundSystem().play("Resources/FX/Victory.mp3");
			m_IsVictory = true;
			break;
		default:
			break;
		}
	}

	void PetterPepperComponent::UpdateSprite()
	{
		//make death and victory state
		if (m_IsHit || m_IsVictory)
			return;

		Direction dir = m_MovementComponent->GetMovement();


		switch (dir)
		{
		case Direction::NONE:
			m_SpriteComponent->SetActiveAnimation("Idle");
			break;
		case Direction::LEFT:
			m_SpriteComponent->SetActiveAnimation("Move");
			m_SpriteComponent->SetFlipState(false);
			break;
		case Direction::RIGHT:
			m_SpriteComponent->SetActiveAnimation("Move");
			m_SpriteComponent->SetFlipState(true);
			break;
		case Direction::UP:
			m_SpriteComponent->SetActiveAnimation("MoveForward");
			break;
		case Direction::DOWN:
			m_SpriteComponent->SetActiveAnimation("MoveBackwards");
			break;
		default:
			break;
		}
	}


}