#pragma once
#include "BurgerStructs.h"
#include "glm/glm.hpp"
#include "GameObject.h"
#include <memory>
#include <vector>

namespace Burger {
	class PrefabCreator {
	public:
		static std::shared_ptr<dae::GameObject> CreatePlayerPrefab(point pos);
		static std::shared_ptr<dae::GameObject> CreatePlatformPrefab(point pos, int tilling);
		static std::shared_ptr<dae::GameObject> CreateLadderPrefab(point pos, int tilling);
		static std::shared_ptr<dae::GameObject> CreatTopBurgerPrefab(point pos);
		static std::shared_ptr<dae::GameObject> CreatLettuceBurgerPrefab(point pos);
		static std::shared_ptr<dae::GameObject> CreatTomatoBurgerPrefab(point pos);
		static std::shared_ptr<dae::GameObject> CreatLowerBurgerPrefab(point pos);
		static std::shared_ptr<dae::GameObject> CreateEnemySpawner(std::vector<point> spawnPoint);
		static std::shared_ptr<dae::GameObject> CreatBurgerCathcherPrefab(point pos);


		//Enemies
		static std::shared_ptr<dae::GameObject> CreateEggEnemy(point pos);
		static std::shared_ptr<dae::GameObject> CreatWorstEnemyrPrefab(point pos);
		static std::shared_ptr<dae::GameObject> CreateSpikey(point pos);







	private:
		static int m_PlayerCount;
	};



}