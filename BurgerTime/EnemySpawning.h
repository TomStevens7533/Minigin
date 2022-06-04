#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "Subject.h"
#include "BurgerStructs.h"
#include <map>
namespace Burger {


	class GameObject;
	class ScoreDisplayComponent;
	class EnemySpawnComponent final : public dae::BaseComponent, public dae::Observer, public dae::Subject
	{
	public:
		EnemySpawnComponent(std::vector<point>& vec, std::map<EnemyType, EnemySpawnInfo>& enemyMap);
		void Render() const override {};
		void Update() override { };
		void LateUpdate() override;
		virtual void Start() override;

		EnemySpawnComponent(const EnemySpawnComponent& other) = delete;
		EnemySpawnComponent(EnemySpawnComponent&& other) = delete;
		EnemySpawnComponent& operator=(const EnemySpawnComponent& other) = delete;
		EnemySpawnComponent& operator=(EnemySpawnComponent&& other) = delete;

		void onNotify(const BaseComponent* entity, int event, dae::EventArgs* args = nullptr) override;
	private:
		std::shared_ptr<dae::GameObject> GetEnemyPrefab(EnemyType type, const point pos, int points);
		void SpawnEnemy();

	private:
		std::vector<point> m_SpawnPoints;
		std::map<EnemyType, EnemySpawnInfo> m_EnemyMap;
		float m_MaxSpawnTime = 0.f;
		float m_RandSpawnTime = 2.f;
		float m_BaseSpawnTime = 1.f;
		float m_CurrentSpawnTime = 0.f;
	};
}
