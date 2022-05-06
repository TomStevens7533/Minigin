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


		//Anims
		m_SpriteComponent->AddAnimation("MoveBackwards", 0, 0, 3, 1);
		m_SpriteComponent->AddAnimation("Move", 3, 0, 6, 1);
		m_SpriteComponent->AddAnimation("MoveForward", 6, 0, 9, 1);

		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_BUTTON_EAST, 'A', new DamageCommand(healthCom, 10), KeyState::PRESSED);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_LEFT,37, new MoveLeftCommand(this), KeyState::DOWN);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveRightCommand(this), KeyState::DOWN);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_UP,38, new MoveUpCommand(this), KeyState::DOWN);
		m_InputComponent->AddCommand(ControllerButton::GAMEPAD_DPAD_DOWN,40, new MoveDownCommand(this), KeyState::DOWN);

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

	//Movement
	void PetterPepperComponent::MoveLeft()
	{
		glm::vec2 getCurrDimensions = m_SpriteComponent->GetCurrentAnimDimensions();
		glm::vec3 newPos = GetAttachedGameObject()->GetTransform().GetPosition();
		ColliderInfo* info = m_pParent->GetScene()->IsPointInCollider(glm::vec2{ newPos.x - getCurrDimensions.x, newPos.y }, "Floor");

		if (info != nullptr) {
			m_SpriteComponent->SetFlipState(false);
			m_SpriteComponent->SetActiveAnimation("Move");
			m_RigidBodyComp->SetVelocityX(-5.f);
			ServiceLocator::GetSoundSystem().play(1, 50.f);


		}

	}

	void PetterPepperComponent::MoveUp()
	{
		glm::vec2 getCurrDimensions = m_SpriteComponent->GetCurrentAnimDimensions();
		glm::vec3 newPos = GetAttachedGameObject()->GetTransform().GetPosition();
		
		//Get bottom center of petter pepper
		ColliderInfo* info = m_pParent->GetScene()->IsPointInCollider(glm::vec2{ newPos.x - (getCurrDimensions.x / 2.f), newPos.y }, "Ladder");
		if (info != nullptr) {
			m_SpriteComponent->SetActiveAnimation("MoveForward");
			m_RigidBodyComp->SetVelocityY(-5.f);
			ServiceLocator::GetSoundSystem().play(1, 50.f);
		}


	}

	void PetterPepperComponent::MoveRight()
	{
		glm::vec3 newPos = GetAttachedGameObject()->GetTransform().GetPosition();
		ColliderInfo* info = m_pParent->GetScene()->IsPointInCollider(glm::vec2{ newPos.x, newPos.y }, "Floor");
		
		if (info != nullptr) {
			m_SpriteComponent->SetActiveAnimation("Move");
			m_SpriteComponent->SetFlipState(true);
			m_RigidBodyComp->SetVelocityX(5.f);
			ServiceLocator::GetSoundSystem().play(0, 50.f);
		}
	}

	void PetterPepperComponent::MoveDown()
	{
		glm::vec2 getCurrDimensions = m_SpriteComponent->GetCurrentAnimDimensions();
		glm::vec3 newPos = GetAttachedGameObject()->GetTransform().GetPosition();

		ColliderInfo* info = m_pParent->GetScene()->IsPointInCollider(glm::vec2{ newPos.x - (getCurrDimensions.x / 2.f), newPos.y + (getCurrDimensions.y / 2.f) }, "Ladder");
		if (info != nullptr) {
			ServiceLocator::GetSoundSystem().play(0, 50.f);
			m_SpriteComponent->SetActiveAnimation("MoveBackwards");
			m_RigidBodyComp->SetVelocityY(5.f);
		}
	}

}

