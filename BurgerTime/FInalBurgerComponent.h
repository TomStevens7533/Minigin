#pragma once
#include "BaseComponent.h"
#include "structs.h"
#include "Subject.h"

namespace dae { class BoxColliderComponent; }
namespace Burger {
	struct ColliderInfo;
	class FinalBurgerComponent  final : public dae::BaseComponent, public dae::Subject
	{
	public:
		FinalBurgerComponent(int fullBurger);
		void Render() const override;
		void Update() override;
		void FixedUpdate() override;
		virtual void Start() override;

		FinalBurgerComponent(const FinalBurgerComponent& other) = delete;
		FinalBurgerComponent(FinalBurgerComponent&& other) = delete;
		FinalBurgerComponent& operator=(const FinalBurgerComponent& other) = delete;
		FinalBurgerComponent& operator=(FinalBurgerComponent&& other) = delete;

		void OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo);
	private:
		dae::BoxColliderComponent* m_BoxColliderComp;
		int m_CurrentBunPieces = 0;
		int m_MaxBunPieces = 0;


	};
}