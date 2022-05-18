#pragma once
#include "BaseComponent.h"
namespace dae {
	enum class HorizontalDirection {
		NONE,
		LEFT,
		RIGHT
	};
	enum class VerticalDirection {
		NONE,
		UP,
		DOWN
	};
	class BoxColliderComponent;
	class MovementComponent : public BaseComponent
	{
	public:
		MovementComponent(float movementVelocity);
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() const override { };

		void SetNewHorizontalDirection(HorizontalDirection newDir);
		void SetNewVerticalDirection(VerticalDirection newDir);

		inline bool GetIsMovingVertically() { return m_IsMovingVertically; }
		inline bool GetIsMovingHorizontally() { return m_IsMovingHorizontally; }

	private:
		HorizontalDirection m_CurrentHorizonDirection = HorizontalDirection::NONE;
		VerticalDirection m_CurrentVertoicalDirection = VerticalDirection::NONE;

		BoxColliderComponent* m_ColliderComponent;
		bool m_IsMovingVertically{ false };
		bool m_IsMovingHorizontally{ false };
		float m_Velocity{};

	};
}
