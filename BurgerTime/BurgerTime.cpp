#include "BurgerTimePCH.h"
#include "BurgerTime.h"
#include "ResourceManager.h"
#include "Parser.h"
#include "SceneManager.h"
#include "Scene.h"

using namespace Burger;
void BurgerTime::Initialize()
{
	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Data/");


	//for (auto& mapElement : pr.GeLevelObject()) {
	//	//Player Creation
	//	if (mapElement.first == "PeterPepperPrefab") {
	//		CreatePlayer(mapElement.second);
	//	}
	//	else if (mapElement.first == "PlatformSoloPrefab") {
	//		CreatePlatform(mapElement.second, 2);
	//	}
	//	else if (mapElement.first == "PlatformLongPrefab") {
	//		CreatePlatform(mapElement.second, 10);
	//	}
	//	else if (mapElement.first == "LadderLongPrefab") {
	//		CreateLadder(mapElement.second, 12);
	//	}
	//	else if (mapElement.first == "LadderShortPrefab") {
	//		CreateLadder(mapElement.second, 10);
	//	}
	//	else if (mapElement.first == "TopBun") {
	//		CreateTopBurger(mapElement.second);
	//	}
	//	else if (mapElement.first == "Lettuce") {
	//		CreateLettuce(mapElement.second);

	//	}
	//	else if (mapElement.first == "Tomato") {
	//		CreateTomato(mapElement.second);

	//	}
	//	else if (mapElement.first == "LowerBun") {
	//		CreateLowerBun(mapElement.second);

	//	}
	//	else if (mapElement.first == "BurgerCatcher") {
	//		CreateBurgerCatcher(mapElement.second);

	//	}

	CreateLevel1();
}

void BurgerTime::CreateLevel1()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level1");

	Parser pr("../Data/Level_1.json");


	scene.Start();

}

