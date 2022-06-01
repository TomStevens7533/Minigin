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
#include "BurgerTimeManager.h"

using namespace Burger;
void BurgerTime::Initialize()
{
	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("Resources/");
	//SEED
	srand(static_cast<int>(time(NULL)));

	CreateLevel1();
	GameManager::GetInstance().SetBurgerGame(this);
}

void BurgerTime::CreateLevel1()
{
	dae::SceneManager::GetInstance().DestroyScene("Level1");
	
	m_currentLevelIdx = 1;
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("Level1");
	CreateLevel("Resources/Level_1.json", &scene);
	//dae::SceneManager::GetInstance().QueueNewScene(&scene);
	scene.Start();
}

void BurgerTime::CreateLevel(const std::string& path, dae::Scene* currScene)
{
	try
	{
		LevelCreator::CreateLevel(path, currScene);
	}
	catch (const ParserException& e)
	{
		std::cerr << "PARSER EXCEPTION: " << e.what() << std::endl;
	}
	catch (const std::bad_cast& e)
	{
		std::cout << e.what() << '\n';
	}

}

unsigned int BurgerTime::GetCurrentStage()
{
	return m_currentLevelIdx;
}

void BurgerTime::LoadStage(unsigned int level)
{
	switch (level)
	{
	case 1:
		CreateLevel1();
		break;
	default:
		break;
	}
}

