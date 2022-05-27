#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae {

	struct AttackArgs : public EventArgs
	{
		int pepperShots;
	};
	class BoxColliderComponent;
	class AttackComponent : public BaseComponent, public Subject
	{
	public:
		AttackComponent() = default;
		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		virtual void Start() override;
		void Fire();

		AttackComponent(const AttackComponent& other) = delete;
		AttackComponent(AttackComponent&& other) = delete;
		AttackComponent& operator=(const AttackComponent& other) = delete;
		AttackComponent& operator=(AttackComponent&& other) = delete;
	private:
		std::shared_ptr<GameObject> m_pWeaponGameobject;
		BoxColliderComponent* m_pPepperCollider = nullptr;
		bool m_IsFiring = false;
		float m_MaxPepperTime = 0.15f;
		float m_CurrentPeperTime = 0.f;
		static int m_PepperShots;
	};
}
