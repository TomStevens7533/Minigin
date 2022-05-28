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
	/*	else if (mapElement.first == "PlatformSoloPrefab") {
			CreatePlatform(mapElement.second, 2);
		}
		else if (mapElement.first == "PlatformLongPrefab") {
			CreatePlatform(mapElement.second, 10);
		}
		else if (mapElement.first == "LadderLongPrefab") {
			CreateLadder(mapElement.second, 12);
		}
		else if (mapElement.first == "LadderShortPrefab") {
			CreateLadder(mapElement.second, 10);
		}
		else if (mapElement.first == "TopBun") {
			CreateTopBurger(mapElement.second);
		}
		else if (mapElement.first == "Lettuce") {
			CreateLettuce(mapElement.second);

		}
		else if (mapElement.first == "Tomato") {
			CreateTomato(mapElement.second);

		}
		else if (mapElement.first == "LowerBun") {
			CreateLowerBun(mapElement.second);

		}
		else if (mapElement.first == "BurgerCatcher") {
			CreateBurgerCatcher(mapElement.second);

		}*/
	}


 
	scene.Start();

}

