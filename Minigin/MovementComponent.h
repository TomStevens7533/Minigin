#pragma once
#include "BaseComponent.h"
namespace dae {
	enum class Direction {
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	class BoxColliderComponent;
	class MovementComponent : public BaseComponent
	{
	public:
		MovementComponent(float movementVelocity);
		virtual void Start() override;
		virtual void Update() override {};
		virtual void LateUpdate() override;
		virtual void Render() const override { };

		void SetNewDirection(Direction newDir);
	private:
		Direction m_CurrentDirection = Direction::NONE;
		BoxColliderComponent* m_ColliderComponent;
		float m_Velocity{};
		
	};
}
