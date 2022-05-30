#include "BurgerTimePCH.h"
#include "BurgerTime.h"
#include "ResourceManager.h"
#include "Parser.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PrefabCreator.h"
#include "TextureComponent.h"
#include "GameObject.h"

using namespace Burger;
void BurgerTime::Initialize()
{
	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("Resources/");


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

	for (auto& mapElement : pr.GeLevelObject()) {
		//Player Creation
		if (mapElement.first == "PeterPepperPrefab") {
			for (point elementPos : mapElement.second)
			{
				auto pepper = PrefabCreator::CreatePlayerPrefab(elementPos);
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

			auto spawner = PrefabCreator::CreateEnemySpawner(mapElement.second);
			scene.Add(spawner);
		}


		//els
		// 
		// e if (mapElement.first == "Lettuce") {
		//	CreateLettuce(mapElement.second);

		//}
		//else if (mapElement.first == "Tomato") {
		//	CreateTomato(mapElement.second);

		//}
		//else if (mapElement.first == "LowerBun") {
		//	CreateLowerBun(mapElement.second);

		//}
		//else if (mapElement.first == "BurgerCatcher") {
		//	CreateBurgerCatcher(mapElement.second);

		//}
	}


 
	scene.Start();

}

