#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "BurgerStructs.h"
#include <map>
namespace Burger {

	class GameObject;
	class EnemySpawnComponent final : public dae::BaseComponent, public dae::Observer
	{
	public:
		EnemySpawnComponent(std::vector<point>& vec, std::map<std::string, EnemySpawnInfo>& enemyMap);
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
		std::shared_ptr<dae::GameObject> GetEnemyPrefab(const std::string& name, const point pos);
		void SpawnEnemy();

	private:
		std::vector<point> m_SpawnPoints;
		std::map<std::string, EnemySpawnInfo> m_EnemyMap;

		float m_MaxSpawnTime = 0.f;
		float m_RandSpawnTime = 0.5f;
		float m_BaseSpawnTime = 0.5f;
		float m_CurrentSpawnTime = 0.f;
	};
}
