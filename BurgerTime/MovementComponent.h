#pragma once
#include "BaseComponent.h"
#include "structs.h"
#include "BoxColliderComponent.h"
namespace Burger {

	class BoxColliderComponent;
	class MovementComponent : public dae::BaseComponent
	{
	public:
		MovementComponent(float movementVelocity);
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() const override { };

		void SetNewHorizontalDirection(dae::HorizontalDirection newDir);
		void SetNewVerticalDirection(dae::VerticalDirection newDir);

		dae::HorizontalDirection GetHorizonDir() { return m_CurrentHorizonDirection; }
		dae::VerticalDirection GetVerticalDir() { return m_CurrentVertoicalDirection; }


		const inline bool GetIsMovingVertically() const { return m_IsMovingVertically; }
		const inline bool GetIsMovingHorizontally() const { return m_IsMovingHorizontally; }

		glm::vec2 GetCenterPos() const;

	private:
		dae::HorizontalDirection m_CurrentHorizonDirection = dae::HorizontalDirection::NONE;
		dae::VerticalDirection m_CurrentVertoicalDirection = dae::VerticalDirection::NONE;

		dae::BoxColliderComponent* m_ColliderComponent;
		bool m_IsMovingVertically{ false };
		bool m_IsMovingHorizontally{ false };
		float m_Velocity{};

	};
}
