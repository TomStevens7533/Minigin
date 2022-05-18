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

	private:
		HorizontalDirection m_CurrentHorizonDirection = HorizontalDirection::NONE;
		VerticalDirection m_CurrentVertoicalDirection = VerticalDirection::NONE;

		BoxColliderComponent* m_ColliderComponent;
		float m_Velocity{};
		
	};
}
