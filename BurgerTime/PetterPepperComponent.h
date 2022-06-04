 
#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae {
	class InputComponent;
	class SpriteComponent;
	class BoxColliderComponent;
}


namespace Burger {

	class MovementComponent;
	//


	class PetterPepperComponent final : public dae::BaseComponent, public dae::Subject, public dae::Observer
	{
	public:
		PetterPepperComponent() = default;
		~PetterPepperComponent();
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override ;
		virtual void Render() const override {};


		void OnCollisionStay(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionExit(const std::shared_ptr<dae::ColliderInfo> otherInfo);

		void onNotify(const BaseComponent* entity, int event, dae::EventArgs* args = nullptr) override;

		void UpdateSprite();


		PetterPepperComponent(const PetterPepperComponent& other) = delete;
		PetterPepperComponent(PetterPepperComponent&& other) = delete;
		PetterPepperComponent& operator=(const PetterPepperComponent& other) = delete;
		PetterPepperComponent& operator=(PetterPepperComponent&& other) = delete;

	private:
		dae::SpriteComponent* m_SpriteComponent;
		MovementComponent* m_MovementComponent;
		float m_MaxVictoryDance = 2.f;
		float m_CurrentVictroyDance = 0.f;

		bool m_IsVictory = false;
		bool m_IsHit = false;

		static bool m_IsFinished;
		static int m_PepperAmountInGame;
	};

}

