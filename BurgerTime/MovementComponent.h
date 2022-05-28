#pragma once
#include "BaseComponent.h"
#include "structs.h"
namespace dae {

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

		HorizontalDirection GetHorizonDir() { return m_CurrentHorizonDirection; }
		VerticalDirection GetVerticalDir() { return m_CurrentVertoicalDirection; }


		const inline bool GetIsMovingVertically() const { return m_IsMovingVertically; }
		const inline bool GetIsMovingHorizontally() const { return m_IsMovingHorizontally; }

		glm::vec2 GetCenterPos() const;

	private:
		HorizontalDirection m_CurrentHorizonDirection = HorizontalDirection::NONE;
		VerticalDirection m_CurrentVertoicalDirection = VerticalDirection::NONE;

		BoxColliderComponent* m_ColliderComponent;
		bool m_IsMovingVertically{ false };
		bool m_IsMovingHorizontally{ false };
		float m_Velocity{};

	};
}
