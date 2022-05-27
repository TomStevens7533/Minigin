#include "MiniginPCH.h"
#include "PetterPepperComponent.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Command.cpp"
#include "SceneObject.h"
#include "Scene.h"
#include "AttackComponent.h"
#include "BoxColliderComponent.h"
#include "structs.h"
#include "MathHelper.h"
#include "MovementComponent.h"

namespace dae {
	void PetterPepperComponent::Start()
	{
		m_InputComponent = GetAttachedGameObject()->GetComponent<InputComponent>();
		m_SpriteComponent = GetAttachedGameObject()->GetComponent<SpriteComponent>();
		m_ColliderComponent = GetAttachedGameObject()->GetComponent<BoxColliderComponent>();

		m_MovementComp = GetAttachedGameObject()->GetComponent<MovementComponent>();
		auto attackComp = GetAttachedGameObject()->GetComponent<AttackComponent>();





		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_BUTTON_EAST, 'A', new AttackCommand(attackComp), KeyState::PRESSED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_LEFT, 37, new MoveLeftEnterCommand(this), KeyState::DOWN);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveRightEnterCommand(this), KeyState::DOWN);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_UP, 38, new MoveUpEnterCommand(this), KeyState::DOWN);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_DOWN, 40, new MoveDownEnterCommand(this), KeyState::DOWN);


		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_LEFT, 37, new MoveLeftExitCommand(this), KeyState::RELEASED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveRightExitCommand(this), KeyState::RELEASED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_UP, 38, new MoveUpExitCommand(this), KeyState::RELEASED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_DOWN, 40, new MoveDownExitCommand(this), KeyState::RELEASED);



		//Adds itself as observor fol collision events
		if (m_ColliderComponent) {
			ColliderCallbacks colBack;
			colBack.OverlapEnterFunc = std::bind(&PetterPepperComponent::OnCollisionEnter, this, std::placeholders::_1);
			colBack.OverlopExitFunc = std::bind(&PetterPepperComponent::OnCollisionExit, this, std::placeholders::_1);
			colBack.OverlapStayFunc = std::bind(&PetterPepperComponent::OnCollisionStay, this, std::placeholders::_1);

			m_ColliderComponent->AddListener(colBack);
		}

	}

	void PetterPepperComponent::Update()
	{

	}

	void PetterPepperComponent::LateUpdate()
	{
		//Reser movement
		m_IsOnLadderDown = false;
		m_IsOnLadderUp = false;
		m_IsOnFloorRight = false;
		m_IsOnFloorLeft = false;
	}

	void PetterPepperComponent::Render() const
	{

	}

	void PetterPepperComponent::onNotify(const BaseComponent*, int , EventArgs* )
	{
		////Getevents
		//ColliderInfo colInfo;
		//ColliderInfo pepperCoIInfo = m_ColliderComponent->GetColliderInfo();
		//CollisionArgs* colArgs;
		//glm::vec2 searchPos1;
		//glm::vec2 searchPos2;

		//switch (event)
		//{
		//case EventType::OnCollisionStay:
		//	//Change to dynamic safety check
		//	colArgs = static_cast<CollisionArgs*>(args);

		//	
		//	colInfo = colArgs->info;

		//	if (colInfo.tag == "Ladder") {

		//		//UP
		//		searchPos1.x = pepperCoIInfo.m_ColliderRect.x + (pepperCoIInfo.m_ColliderRect.width / 2.f);
		//		searchPos1.y = pepperCoIInfo.m_ColliderRect.y + (pepperCoIInfo.m_ColliderRect.height / 2.f);

		//		//Down
		//		searchPos2.x = pepperCoIInfo.m_ColliderRect.x + (pepperCoIInfo.m_ColliderRect.width / 2.f);
		//		searchPos2.y = pepperCoIInfo.m_ColliderRect.y + pepperCoIInfo.m_ColliderRect.height;

		//		if (MathHelper::IsPointInRect(colInfo.m_ColliderRect, searchPos1)) {

		//			m_IsOnLadderUp = true;
		//		}
		//		if (MathHelper::IsPointInRect(colInfo.m_ColliderRect, searchPos2)) {
		//			m_IsOnLadderDown = true;

		//		}
		//	}
		//	if (colInfo.tag == "Floor") {

		//		//right
		//		searchPos1.x = pepperCoIInfo.m_ColliderRect.x + pepperCoIInfo.m_ColliderRect.width;
		//		searchPos1.y = pepperCoIInfo.m_ColliderRect.y + pepperCoIInfo.m_ColliderRect.height;

		//		//left
		//		searchPos2.x = pepperCoIInfo.m_ColliderRect.x;
		//		searchPos2.y = pepperCoIInfo.m_ColliderRect.y + pepperCoIInfo.m_ColliderRect.height;

		//		if (MathHelper::IsPointInRect(colInfo.m_ColliderRect, searchPos1)) {
		//			m_IsOnFloorRight = true;
		//		}
		//		if (MathHelper::IsPointInRect(colInfo.m_ColliderRect, searchPos2)) {
		//			m_IsOnFloorLeft = true;
		//		}


		//	}
		//default:
		//	break;
		//}
	}

	void PetterPepperComponent::MoveLeftEnter()
	{
		if (m_IsOnFloorLeft) {
			if (m_SpriteComponent != nullptr) {
				m_SpriteComponent->SetActiveAnimation("Move");
				m_SpriteComponent->SetFlipState(false);
			}
			m_MovementComp->SetNewHorizontalDirection(HorizontalDirection::LEFT);
			return;
		}
		m_MovementComp->SetNewHorizontalDirection(HorizontalDirection::NONE);

	}

	void PetterPepperComponent::MoveRightEnter()
	{
		if (m_IsOnFloorRight) {
			if (m_SpriteComponent != nullptr) {
				m_SpriteComponent->SetActiveAnimation("Move");
				m_SpriteComponent->SetFlipState(true);
			}
			m_MovementComp->SetNewHorizontalDirection(HorizontalDirection::RIGHT);
			return;

		}
		m_MovementComp->SetNewHorizontalDirection(HorizontalDirection::NONE);

	}

	void PetterPepperComponent::MoveUpEnter()
	{

		if (m_IsOnLadderUp) {
			if (m_SpriteComponent != nullptr) {
				m_SpriteComponent->SetActiveAnimation("MoveForward");
				m_SpriteComponent->SetFlipState(false);
			}
			m_MovementComp->SetNewVerticalDirection(VerticalDirection::UP);
			return;
		}
		m_MovementComp->SetNewVerticalDirection(VerticalDirection::NONE);

	}

	void PetterPepperComponent::MoveDownEnter()
	{
		if (m_IsOnLadderDown) {
			if (m_SpriteComponent != nullptr) {
				m_SpriteComponent->SetActiveAnimation("MoveBackwards");
				m_SpriteComponent->SetFlipState(false);
			}
			m_MovementComp->SetNewVerticalDirection(VerticalDirection::DOWN);
			return;
		}
		m_MovementComp->SetNewVerticalDirection(VerticalDirection::NONE);
	}

	void PetterPepperComponent::MoveLeftExit()
	{
		m_MovementComp->SetNewHorizontalDirection(HorizontalDirection::NONE);
	}

	void PetterPepperComponent::MoveRightExit()
	{
		m_MovementComp->SetNewHorizontalDirection(HorizontalDirection::NONE);

	}

	void PetterPepperComponent::MoveUpExit()
	{
		m_MovementComp->SetNewVerticalDirection(VerticalDirection::NONE);

	}

	void PetterPepperComponent::MoveDownExit()
	{
		m_MovementComp->SetNewVerticalDirection(VerticalDirection::NONE);
	}

	void PetterPepperComponent::OnCollisionStay(const std::shared_ptr<ColliderInfo> otherInfo)
	{
		glm::vec2 searchPos1;
		glm::vec2 searchPos2;
		ColliderInfo info = m_ColliderComponent->GetColliderInfo();


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

	void PetterPepperComponent::OnCollisionEnter(const std::shared_ptr<ColliderInfo> otherInfo)
	{

	}

	void PetterPepperComponent::OnCollisionExit(const std::shared_ptr<ColliderInfo> otherInfo)
	{

	}

}
//	//MoveState
//	void MoveState::Entry(PetterPepperComponent& ai)
//	{
//
//	}
//
//	dae::PepperState* MoveState::UpdateState(PetterPepperComponent& pepper)
//	{
//		//Check Input
//		//if change 
//		//go entry
//	}
//
//	void MoveState::Exit(PetterPepperComponent& pepper)
//	{
//		pepper.m_MovementComp->SetNewHorizontalDirection(HorizontalDirection::NONE);
//		pepper.m_MovementComp->SetNewVerticalDirection(VerticalDirection::NONE);
//	}
//
//
//	//AttackState
//	void AttackState::Entry(PetterPepperComponent& ai)
//	{
//
//	}
//
//	dae::PepperState* AttackState::UpdateState(PetterPepperComponent& pepper)
//	{
//
//	}
//
//	void AttackState::Exit(PetterPepperComponent&)
//	{
//
//	}
//
//}
//
