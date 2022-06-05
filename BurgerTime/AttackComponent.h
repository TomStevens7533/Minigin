#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "AttackComponent.h"
#include "BoxColliderComponent.h"

namespace Burger {

	struct AttackArgs : public dae::EventArgs
	{
		int pepperShots;
	};
	class GameObject;
	class AttackComponent final : public dae::BaseComponent, public dae::Subject
	{
	public:
		AttackComponent() = default;
		void Render() const override;
		void Update() override;
		void FixedUpdate() override; 
		virtual void Start() override;
		void Fire();

		AttackComponent(const AttackComponent& other) = delete;
		AttackComponent(AttackComponent&& other) = delete;
		AttackComponent& operator=(const AttackComponent& other) = delete;
		AttackComponent& operator=(AttackComponent&& other) = delete;
	private:
		std::shared_ptr<dae::GameObject> m_pWeaponGameobject;
		dae::BoxColliderComponent* m_pPepperCollider = nullptr;
		bool m_IsFiring = false;
		float m_MaxPepperTime = 0.15f;
		float m_CurrentPeperTime = 0.f;
		static int m_PepperShots;
	};
}
