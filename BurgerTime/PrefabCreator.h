#pragma once
#include "BurgerStructs.h"
#include "glm/glm.hpp"
#include "GameObject.h"
#include <memory>
#include <vector>
#include <map>


namespace Burger {
	class LivesDisplayComponent;
	class ScoreDisplayComponent;
	class PepperDisplayComponent;

	class PrefabCreator final {
	public:
		static std::shared_ptr<dae::GameObject> CreatePlayerPrefab(point pos, int playerID);
		static std::shared_ptr<dae::GameObject> CreatePlayableWorstPrefab(point pos, int score, int playerID);



		static std::shared_ptr<dae::GameObject> CreatePlatformPrefab(point pos, int tilling);
		static std::shared_ptr<dae::GameObject> CreateLadderPrefab(point pos, int tilling);
		static std::shared_ptr<dae::GameObject> CreatTopBurgerPrefab(point pos);
		static std::shared_ptr<dae::GameObject> CreatLettuceBurgerPrefab(point pos);
		static std::shared_ptr<dae::GameObject> CreatTomatoBurgerPrefab(point pos);
		static std::shared_ptr<dae::GameObject> CreatLowerBurgerPrefab(point pos);
		static std::shared_ptr<dae::GameObject> CreateEnemySpawner(std::vector<point> spawnPoint, std::map<EnemyType,  EnemySpawnInfo>& enemyMap);
		static std::shared_ptr<dae::GameObject> CreatBurgerCathcherPrefab(point pos);

		//UI
		static std::shared_ptr<dae::GameObject> CreateScoreUI(point pos);
		static std::shared_ptr<dae::GameObject> CreatePepperUI(point pos);
		static std::shared_ptr<dae::GameObject> CreateLivesUI(point pos);
		static std::shared_ptr<dae::GameObject> CreateMainMenu();
		static std::shared_ptr<dae::GameObject> CreateGameOver();


		//Enemies
		static std::shared_ptr<dae::GameObject> CreateEggEnemy(point pos, int score);
		static std::shared_ptr<dae::GameObject> CreatWorstEnemyrPrefab(point pos, int score);
		static std::shared_ptr<dae::GameObject> CreateSpikey(point pos, int score);







	private:
		static int m_PlayerCount;
	};



}