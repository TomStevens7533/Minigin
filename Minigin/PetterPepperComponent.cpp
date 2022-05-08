#include "MiniginPCH.h"
#include "PetterPepperComponent.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Command.cpp"
#include "SceneObject.h"
#include "Scene.h"
#include "ServiceLocator.h"
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


		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_LEFT, 37, new MoveExitCommand(movementComp), KeyState::RELEASED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveExitCommand(movementComp), KeyState::RELEASED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_UP, 38, new MoveExitCommand(movementComp), KeyState::RELEASED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_DOWN, 40, new MoveExitCommand(movementComp), KeyState::RELEASED);

		ServiceLocator::GetSoundSystem().load(0, "../Data/footstep.mp3");

		ServiceLocator::GetSoundSystem().load(1, "../Data/wandel.mp3");



	}

	void PetterPepperComponent::Update()
	{
		if (!m_InputComponent->IsTriggered()) {
			m_SpriteComponent->SetActiveAnimation("MoveBackwards");
		}
	}

	void PetterPepperComponent::LateUpdate()
	{

	}

	void PetterPepperComponent::Render() const
	{

	}

}

