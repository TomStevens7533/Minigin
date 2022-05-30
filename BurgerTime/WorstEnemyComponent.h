#pragma once
#include "BaseComponent.h"
#include "Subject.h"
namespace Burger {
	class WorstEnemyComponent final : public dae::BaseComponent, public dae::Subject {
	public:
		WorstEnemyComponent() = default;
		void Render() const override {};
		void Update() override {};
		void LateUpdate() override {};
		virtual void Start() override;

		WorstEnemyComponent(const WorstEnemyComponent& other) = delete;
		WorstEnemyComponent(WorstEnemyComponent&& other) = delete;
		WorstEnemyComponent& operator=(const WorstEnemyComponent& other) = delete;
		WorstEnemyComponent& operator=(WorstEnemyComponent&& other) = delete;


		void OnCollisionEnter(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionStay(const std::shared_ptr<dae::ColliderInfo> otherInfo);
		void OnCollisionExit(const std::shared_ptr<dae::ColliderInfo> otherInfo);

	private:
	};
}
