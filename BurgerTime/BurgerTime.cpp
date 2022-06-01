#include "BurgerTimePCH.h"
#include "BurgerTime.h"
#include "ResourceManager.h"
#include "Parser.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PrefabCreator.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "PetterPepperComponent.h"
#include "AttackComponent.h"
#include "LivesDisplayComponent.h"
#include "PepperDisplayComponent.h"
#include "ScoreDisplayComponent.h"

using namespace Burger;
void BurgerTime::Initialize()
{
	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("Resources/");

	//SEED
	srand(static_cast<int>(time(NULL)));

	CreateLevel1();
}

void BurgerTime::CreateLevel1()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	Parser pr("Resources/Level_1.json");

	auto go = std::make_shared<dae::GameObject>();
	auto texComp = std::make_shared<dae::TextureComponent>("background.jpg");
	go->SetPosition({ 0,0 });
	go->AddComponent<dae::TextureComponent>(texComp);
	scene.Add(go);

	std::shared_ptr<dae::GameObject> m_ScoreUI;
	std::shared_ptr<dae::GameObject> m_HealthUI;
	std::shared_ptr<dae::GameObject> m_PepperUI;
	for (auto& mapElement : pr.GeLevelObject()) {
		//Create UI Elements


		if (mapElement.first == "ScoreUI") {

			for (point elementPos : mapElement.second)
			{
				auto scoreUI = PrefabCreator::CreateScoreUI(elementPos);
				m_ScoreUI = (scoreUI);
				scene.Add(scoreUI);
			}
		}
		else if (mapElement.first == "LiveUI") {

			for (point elementPos : mapElement.second)
			{
				auto liveUi = PrefabCreator::CreateLivesUI(elementPos);
				m_HealthUI = (liveUi);
				scene.Add(liveUi);

			}
		}
		else if (mapElement.first == "PepperUI") {

			for (point elementPos : mapElement.second)
			{
				auto pepperUI = PrefabCreator::CreatePepperUI(elementPos);
				m_PepperUI = pepperUI;
				scene.Add(pepperUI);


			}
		}



	}
	for (auto& mapElement : pr.GeLevelObject()) {
		//Create prefabs

		if (mapElement.first == "PeterPepperPrefab") {
			for (point elementPos : mapElement.second)
			{
				auto pepper = PrefabCreator::CreatePlayerPrefab(elementPos);
				//Set Score UI

				scene.Add(pepper);
			}
		}
		else if (mapElement.first == "PlatformSoloPrefab") {

			for (point elementPos : mapElement.second)
			{
				auto pepper = PrefabCreator::CreatePlatformPrefab(elementPos, 2);
				scene.Add(pepper);
			}
		}
		else if (mapElement.first == "PlatformLongPrefab") {
			for (point elementPos : mapElement.second)
			{
				auto pepper = PrefabCreator::CreatePlatformPrefab(elementPos, 10);
				scene.Add(pepper);
			}
		}
		else if (mapElement.first == "LadderLongPrefab") {

			for (point elementPos : mapElement.second)
			{
				auto pepper = PrefabCreator::CreateLadderPrefab(elementPos, 12);
				scene.Add(pepper);
			}
		}
		else if (mapElement.first == "LadderShortPrefab") {
			for (point elementPos : mapElement.second)
			{
				auto pepper = PrefabCreator::CreateLadderPrefab(elementPos, 10);
				scene.Add(pepper);
			}
		}
		else if (mapElement.first == "TopBun") {
			for (point elementPos : mapElement.second)
			{
				auto topBurger = PrefabCreator::CreatTopBurgerPrefab(elementPos);
				scene.Add(topBurger);
			}
		}
		else if (mapElement.first == "Lettuce") {
			for (point elementPos : mapElement.second)
			{
				auto letuce = PrefabCreator::CreatLettuceBurgerPrefab(elementPos);
				scene.Add(letuce);
			}
		}
		else if (mapElement.first == "Tomato") {
			for (point elementPos : mapElement.second)
			{
				auto tomato = PrefabCreator::CreatTomatoBurgerPrefab(elementPos);
				scene.Add(tomato);
			}
		}
		else if (mapElement.first == "LowerBun") {
			for (point elementPos : mapElement.second)
			{
				auto lowerbun = PrefabCreator::CreatLowerBurgerPrefab(elementPos);
				scene.Add(lowerbun);
			}
		}
		else if (mapElement.first == "BurgerCatcher") {
			for (point elementPos : mapElement.second)
			{
				auto burerCatch = PrefabCreator::CreatBurgerCathcherPrefab(elementPos);
				scene.Add(burerCatch);
			}
		}
		else if (mapElement.first == "EnemySpawnPoints") {

			auto spawner = PrefabCreator::CreateEnemySpawner(mapElement.second, pr.GetEnemyInfo());
			scene.Add(spawner);
		}


	}
		
	scene.Start();


 
	

}

