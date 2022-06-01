#include "BurgerTimePCH.h"
#include "BurgerTime.h"
#include "ResourceManager.h"
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
#include "LevelCreator.h"

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
	LoadLevel("Resources/Level_1.json");
	
}

void BurgerTime::LoadLevel(const std::string& path)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	try
	{
		LevelCreator::CreateLevel(path, &scene);
	}
	catch (const ParserException& e)
	{
		std::cerr << "PARSER EXCEPTION: " << e.what() << std::endl;
	}
	scene.Start();

}

