#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae {
	class InputComponent;
	class SpriteComponent;
	class BoxColliderComponent;
}


namespace Burger {

	class MovementComponent;
	//


	class PetterPepperComponent final : public dae::BaseComponent
	{
	public:
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() const override;



		void MoveLeftEnter();
		void MoveRightEnter();
		void MoveUpEnter();
		void MoveDownEnter();


		void MoveLeftExit();
		void MoveRightExit();
		void MoveUpExit();
		void MoveDownExit();

		void OnCollisionStay(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionExit(const std::shared_ptr<dae::ColliderInfo> otherInfo);


	protected:

	private:



		dae::InputComponent * m_InputComponent;
		dae::SpriteComponent* m_SpriteComponent;
		dae::BoxColliderComponent* m_ColliderComponent = nullptr;
		MovementComponent* m_MovementComp = nullptr;

		bool m_IsOnLadderUp = false;
		bool m_IsOnLadderDown = false;

		bool m_IsOnFloorRight = false;
		bool m_IsOnFloorLeft = false;

		bool m_IsHit = false;

	};

}

