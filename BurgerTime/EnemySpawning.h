#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "BurgerStructs.h"

namespace Burger {

	class GameObject;
	class EnemySpawnComponent final : public dae::BaseComponent, public dae::Observer
	{
	public:
		EnemySpawnComponent(std::vector<point>& vec);
		void Render() const override {};
		void Update() override {};
		void LateUpdate() override {};
		virtual void Start() override;

		EnemySpawnComponent(const EnemySpawnComponent& other) = delete;
		EnemySpawnComponent(EnemySpawnComponent&& other) = delete;
		EnemySpawnComponent& operator=(const EnemySpawnComponent& other) = delete;
		EnemySpawnComponent& operator=(EnemySpawnComponent&& other) = delete;

		void onNotify(const BaseComponent* entity, int event, dae::EventArgs* args = nullptr) override;
		void SpawnEnemies();
	private:
		std::vector<point> m_SpawnPoints;

		//Max values
		int m_MaxWorstInStage = 4;
		int m_MaxEggInStage = 1;

		//Current Values
		int m_CurrentWorstInStage = 0;
		int m_CurrentEggInStage = 0;
	};
}
