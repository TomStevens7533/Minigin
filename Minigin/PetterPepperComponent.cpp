#include "MiniginPCH.h"
#include "PetterPepperComponent.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Command.cpp"

namespace dae {
	void PetterPepperComponent::Start()
	{
		m_InputComponent = GetAttachedGameObject()->GetComponent<InputComponent>();
		auto healthCom = GetAttachedGameObject()->GetComponent<HealthComponent>();
		m_SpriteComponent = GetAttachedGameObject()->GetComponent<SpriteComponent>();
		auto rigidCom = GetAttachedGameObject()->GetComponent<RigidbodyComponent>();

		//Anims
		m_SpriteComponent->AddAnimation("MoveBackwards", 0, 0, 3, 1);
		m_SpriteComponent->AddAnimation("Move", 3, 0, 6, 1);
		m_SpriteComponent->AddAnimation("MoveForward", 6, 0, 9, 1);

		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_BUTTON_EAST, new DamageCommand(healthCom, 10), KeyState::PRESSED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_LEFT, new MoveLeftCommand(rigidCom, m_SpriteComponent), KeyState::DOWN);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_RIGHT, new MoveRightCommand(rigidCom, m_SpriteComponent), KeyState::DOWN);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_UP, new MoveUpCommand(rigidCom, m_SpriteComponent), KeyState::DOWN);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_DOWN, new MoveDownCommand(rigidCom, m_SpriteComponent), KeyState::DOWN);

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

