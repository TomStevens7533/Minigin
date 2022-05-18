#include "MiniginPCH.h"
#include "PetterPepperComponent.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Command.cpp"
#include "SceneObject.h"
#include "Scene.h"
namespace dae {
	void PetterPepperComponent::Start()
	{
		m_InputComponent = GetAttachedGameObject()->GetComponent<InputComponent>();
		auto healthCom = GetAttachedGameObject()->GetComponent<HealthComponent>();
		m_SpriteComponent = GetAttachedGameObject()->GetComponent<SpriteComponent>();
		m_RigidBodyComp = GetAttachedGameObject()->GetComponent<RigidbodyComponent>();
		auto movementComp = GetAttachedGameObject()->GetComponent<MovementComponent>();



	
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_BUTTON_EAST, 'A', new DamageCommand(healthCom, 10), KeyState::PRESSED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_LEFT,37, new MoveLeftEnterCommand(movementComp), KeyState::PRESSED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveRightEnterCommand(movementComp), KeyState::PRESSED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_UP,38, new MoveUpEnterCommand(movementComp), KeyState::PRESSED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_DOWN,40, new MoveDownEnterCommand(movementComp), KeyState::PRESSED);


		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_LEFT, 37, new MoveHorizontalExitCommand(movementComp), KeyState::RELEASED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveHorizontalExitCommand(movementComp), KeyState::RELEASED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_UP, 38, new MoveVerticalExitCommand(movementComp), KeyState::RELEASED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_DOWN, 40, new MoveVerticalExitCommand(movementComp), KeyState::RELEASED);



	}

	void PetterPepperComponent::Update()
	{
	
	}

	void PetterPepperComponent::LateUpdate()
	{

	}

	void PetterPepperComponent::Render() const
	{

	}

}

