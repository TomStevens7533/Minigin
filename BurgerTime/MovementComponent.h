#pragma once
#include "BaseComponent.h"
#include "BurgerStructs.h"
#include "BoxColliderComponent.h"
namespace Burger {

	class BoxColliderComponent;
	class MovementComponent final : public dae::BaseComponent
	{
	public:
		MovementComponent(float movementVelocity);
		virtual void Start() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() const override { };

		void SetNewDirection(Direction newDir);
		Direction GetDirection() const { return m_CurrentDir; }
		Direction GetMovement() { return m_CurrentDir; }

		void SetChangeMovementDisable(bool isDisabled) { m_IsDisabled = isDisabled; }
		void SetMovementCollisionCheckDisable(bool isDisabled) { m_IsCollisionDisabled = isDisabled; }
		void OnCollisionStay(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		//void SetMovementChange(bool isDisabled) { m_IsDisabled = isDisabled; }




		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

		inline void SetNewVelocity(float newVelocity) {
			m_Velocity = newVelocity;
		}

	private:
		Direction m_CurrentDir = Direction::NONE;
		dae::BoxColliderComponent* m_ColliderComponent = nullptr;
		float m_Velocity{};
		bool m_IsDisabled = false;
		bool m_IsCollisionDisabled = false;
		bool m_IsOnLadderUp = false;
		bool m_IsOnLadderDown = false;

		bool m_IsOnFloorRight = false;
		bool m_IsOnFloorLeft = false;


	};
}
