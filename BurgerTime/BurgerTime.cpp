#include "BurgerTimePCH.h"
#include "BurgerTime.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PrefabCreator.h"
#include "GameObject.h"
#include "LevelCreator.h"
#include "BurgerTimeManager.h"
#include "ServiceLocator.h"


using namespace Burger;
void BurgerTime::Initialize()
{
	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("Resources/");
	//SEED
	srand(static_cast<int>(time(NULL)));

	CreateMainMenu();
	GameManager::GetInstance().SetBurgerGame(this);
}

void BurgerTime::CreateLevel1()
{
	
	m_CurrentLevel = Level::LEVEL1;
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

Level BurgerTime::GetCurrentStage()
{
	return m_CurrentLevel;
}

void BurgerTime::LoadNextStage(Level level)
{
	switch (level)
	{
	case Level::MAIN_MENU:
		CreateLevel1();
		break;
	case Level::LEVEL1:
		CreateMainMenu();
		break;
	default:
		CreateMainMenu();
		break;
	}
}

void BurgerTime::CreateMainMenu()
{
	m_CurrentLevel = Level::MAIN_MENU;
	auto menu = PrefabCreator::CreateMainMenu();
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("MainMenu");
	scene.Add(menu);
	scene.Start();
	ServiceLocator::GetSoundSystem().play(
		ServiceLocator::GetSoundSystem().load("Resources/Music/MainMenuSong.mp3"), 1.f);


}

void BurgerTime::RemoveStage(Level level)
{
	switch (level)
	{
	case Level::MAIN_MENU:
		dae::SceneManager::GetInstance().DestroyScene("MainMenu");
		break;
	case Level::LEVEL1:
		dae::SceneManager::GetInstance().DestroyScene("Level1");
		break;
	case Level::GAME_OVER:
		dae::SceneManager::GetInstance().DestroyScene("GameOver");
		break;
	default:
		dae::SceneManager::GetInstance().DestroyScene("Level1");
		dae::SceneManager::GetInstance().DestroyScene("MainMenu");
		break;
	}
}

void BurgerTime::CreateGameOver()
{
	m_CurrentLevel = Level::GAME_OVER;

	auto menu = PrefabCreator::CreateGameOver();
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("GameOver");
	scene.Add(menu);
	scene.Start();
}

void BurgerTime::LoadStage(Level level)
{
	switch (level)
	{
	case Level::MAIN_MENU:
		CreateMainMenu();
		break;
	case Level::LEVEL1:
		CreateLevel1();
		break;
	case Level::GAME_OVER:
		CreateGameOver();
		break;
	default:
		CreateMainMenu();
		break;
	}
}

