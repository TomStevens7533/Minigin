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

namespace Burger {


	void PetterPepperComponent::Start()
	{
		m_InputComponent = GetAttachedGameObject()->GetComponent<dae::InputComponent>();
		m_SpriteComponent = GetAttachedGameObject()->GetComponent<dae::SpriteComponent>();
		m_ColliderComponent = GetAttachedGameObject()->GetComponent<dae::BoxColliderComponent>();

		m_MovementComp = GetAttachedGameObject()->GetComponent<MovementComponent>();
		auto attackComp = GetAttachedGameObject()->GetComponent<AttackComponent>();

		GameManager::GetInstance().addObserver(this);

		//addObserver(GameManager::GetInstance());

		m_InputComponent->AddCommand(dae::ControllerButton::GAMEPAD_BUTTON_EAST, 'A', new AttackCommand(attackComp), dae::KeyState::PRESSED);
		m_InputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_LEFT, 37, new MoveLeftEnterCommand(this), dae::KeyState::DOWN);
		m_InputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveRightEnterCommand(this), dae::KeyState::DOWN);
		m_InputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_UP, 38, new MoveUpEnterCommand(this), dae::KeyState::DOWN);
		m_InputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_DOWN, 40, new MoveDownEnterCommand(this), dae::KeyState::DOWN);


		m_InputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_LEFT, 37, new MoveLeftExitCommand(this), dae::KeyState::RELEASED);
		m_InputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveRightExitCommand(this), dae::KeyState::RELEASED);
		m_InputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_UP, 38, new MoveUpExitCommand(this), dae::KeyState::RELEASED);
		m_InputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_DOWN, 40, new MoveDownExitCommand(this), dae::KeyState::RELEASED);



		//Adds itself as observor fol collision events
		if (m_ColliderComponent) {
			dae::ColliderCallbacks colBack;
			colBack.OverlapEnterFunc = std::bind(&PetterPepperComponent::OnCollisionEnter, this, std::placeholders::_1);
			colBack.OverlopExitFunc = std::bind(&PetterPepperComponent::OnCollisionExit, this, std::placeholders::_1);
			colBack.OverlapStayFunc = std::bind(&PetterPepperComponent::OnCollisionStay, this, std::placeholders::_1);

			m_ColliderComponent->AddListener(colBack);
		}

	} 

	void PetterPepperComponent::Update()
	{
		if (m_IsVictory) {
		
			if (m_CurrentVictroyDance < m_MaxVictoryDance)
				m_CurrentVictroyDance += dae::Time::GetInstance().GetDeltaTime();
			else
				GameManager::GetInstance().GoToNextLevel();
		}
	}

	void PetterPepperComponent::LateUpdate()
	{
		//Reser movement
		m_IsOnLadderDown = false;
		m_IsOnLadderUp = false;
		m_IsOnFloorRight = false;
		m_IsOnFloorLeft = false;

		if (m_IsHit && m_SpriteComponent->IsActiveInFinalFrame()) {		

			notify(this, PepperEvent::HEALTH_DECREASE);
			m_IsHit = false;
		}
	}

	void PetterPepperComponent::Render() const
	{

	}

	void PetterPepperComponent::MoveLeftEnter()
	{
		if (m_IsOnFloorLeft) {
			if (m_SpriteComponent != nullptr) {
				m_SpriteComponent->SetActiveAnimation("Move");
				m_SpriteComponent->SetFlipState(false);
			}
			m_MovementComp->SetNewHorizontalDirection(dae::HorizontalDirection::LEFT);
			return;
		}
		m_MovementComp->SetNewHorizontalDirection(dae::HorizontalDirection::NONE);

	}

	void PetterPepperComponent::MoveRightEnter()
	{
		if (m_IsOnFloorRight) {
			if (m_SpriteComponent != nullptr) {
				m_SpriteComponent->SetActiveAnimation("Move");
				m_SpriteComponent->SetFlipState(true);
			}
			m_MovementComp->SetNewHorizontalDirection(dae::HorizontalDirection::RIGHT);
			return;

		}
		m_MovementComp->SetNewHorizontalDirection(dae::HorizontalDirection::NONE);

	}

	void PetterPepperComponent::MoveUpEnter()
	{

		if (m_IsOnLadderUp) {
			if (m_SpriteComponent != nullptr) {
				m_SpriteComponent->SetActiveAnimation("MoveForward");
				m_SpriteComponent->SetFlipState(false);
			}
			m_MovementComp->SetNewVerticalDirection(dae::VerticalDirection::UP);
			return;
		}
		m_MovementComp->SetNewVerticalDirection(dae::VerticalDirection::NONE);

	}

	void PetterPepperComponent::MoveDownEnter()
	{
		if (m_IsOnLadderDown) {
			if (m_SpriteComponent != nullptr) {
				m_SpriteComponent->SetActiveAnimation("MoveBackwards");
				m_SpriteComponent->SetFlipState(false);
			}
			m_MovementComp->SetNewVerticalDirection(dae::VerticalDirection::DOWN);
			return;
		}
		m_MovementComp->SetNewVerticalDirection(dae::VerticalDirection::NONE);
	}

	void PetterPepperComponent::MoveLeftExit()
	{
		m_MovementComp->SetNewHorizontalDirection(dae::HorizontalDirection::NONE);
		if (m_MovementComp->GetVerticalDir() == dae::VerticalDirection::NONE) {
			m_SpriteComponent->SetActiveAnimation("Idle");

		}
	}

	void PetterPepperComponent::MoveRightExit()
	{
		m_MovementComp->SetNewHorizontalDirection(dae::HorizontalDirection::NONE);
		if (m_MovementComp->GetVerticalDir() == dae::VerticalDirection::NONE) {
			m_SpriteComponent->SetActiveAnimation("Idle");

		}
	}

	void PetterPepperComponent::MoveUpExit()
	{
		m_MovementComp->SetNewVerticalDirection(dae::VerticalDirection::NONE);
		if (m_MovementComp->GetHorizonDir() == dae::HorizontalDirection::NONE) {
			m_SpriteComponent->SetActiveAnimation("Idle");

		}
	}

	void PetterPepperComponent::MoveDownExit()
	{
		m_MovementComp->SetNewVerticalDirection(dae::VerticalDirection::NONE);
		if (m_MovementComp->GetHorizonDir() == dae::HorizontalDirection::NONE) {
			m_SpriteComponent->SetActiveAnimation("Idle");

		}
	}

	void PetterPepperComponent::OnCollisionStay(const std::shared_ptr<dae::ColliderInfo> otherInfo)
	{
		glm::vec2 searchPos1;
		glm::vec2 searchPos2;
		dae::ColliderInfo info = m_ColliderComponent->GetColliderInfo();


		if (otherInfo->tag == "Ladder") {

			//UP
			searchPos1.x = info.m_ColliderRect.x + (info.m_ColliderRect.width / 2.f);
			searchPos1.y = info.m_ColliderRect.y + (info.m_ColliderRect.height / 2.f);
									
			//Down					
			searchPos2.x = info.m_ColliderRect.x + (info.m_ColliderRect.width / 2.f);
			searchPos2.y = info.m_ColliderRect.y + info.m_ColliderRect.height;

			if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, searchPos1)) {

				m_IsOnLadderUp = true;
			}
			if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, searchPos2)) {
				m_IsOnLadderDown = true;

			}
		}
		if (otherInfo->tag == "Floor") {

			//right
			searchPos1.x = info.m_ColliderRect.x + (info.m_ColliderRect.width / 4.f);
			searchPos1.y = info.m_ColliderRect.y + (info.m_ColliderRect.height);

			////left
			searchPos2.x = info.m_ColliderRect.x + ((info.m_ColliderRect.width) );
			searchPos2.y = info.m_ColliderRect.y + info.m_ColliderRect.height;

			if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, searchPos2)) {
				m_IsOnFloorRight = true;
			}
			if (MathHelper::IsPointInRect(otherInfo->m_ColliderRect, searchPos1)) {
				m_IsOnFloorLeft = true;
			}


		}


	}

	void PetterPepperComponent::OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo)
	{
		//Check enemy hit
		if (otherInfo->tag == "Enemy" && m_IsVictory == false) {
			m_IsHit = true;
			m_SpriteComponent->SetActiveAnimation("Death");
			m_SpriteComponent->SetFlipState(false);
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
			std::cout << "Dance\n";
			m_IsVictory = true;
			break;
		default:
			break;
		}
	}

}
