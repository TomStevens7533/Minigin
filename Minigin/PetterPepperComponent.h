#pragma once
#include "BaseComponent.h"
#include "Subject.h"




namespace dae {
	class InputComponent;
	class SpriteComponent;
	class RigidbodyComponent;
	
	class PetterPepperComponent : public BaseComponent, public Subject
	{
	public:
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() const override;

		void MoveLeft();
		void MoveUp();
		void MoveRight();
		void MoveDown();
	protected:

	private:
		InputComponent* m_InputComponent;
		SpriteComponent* m_SpriteComponent;
		RigidbodyComponent* m_RigidBodyComp;
	};

}

