#pragma warning(disable:4201)
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
	ServiceLocator::GetSoundSystem().SetGlobalVolumeLevel(7.f);

	CreateMainMenu();
	GameManager::GetInstance().SetBurgerGame(this);


	std::cout << "---USER INFO----\n";
	std::cout << "Use controller for input or use keyboard\n";
	std::cout << "--P1-- \n";
	std::cout << "WASD TO MOVE \n";
	std::cout << "Q TO PEPPER \n";
	std::cout << "--P2-- \n";
	std::cout << "ARROWS TO MOVE \n";
	std::cout << "ENTER TO PEPPER \n";


	std::cout << std::endl;



}

void BurgerTime::CreateLevel1()
{
	ServiceLocator::GetSoundSystem().StopAll();
	ServiceLocator::GetSoundSystem().play("Resources/Music/LEVEL1.mp3");

	m_CurrentLevel = Level::LEVEL1;
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("Level1");
	CreateLevel("Resources/Level_2.json", &scene);
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
		CreateLevel2();
		break;
	case Level::LEVEL2:
		CreateLevel3();
		break;
	case Level::LEVEL3:
		CreateMainMenu();
		break;
	default:
		CreateMainMenu();
		break;
	}
}

void BurgerTime::CreateMainMenu()
{
	ServiceLocator::GetSoundSystem().StopAll();
	ServiceLocator::GetSoundSystem().play("Resources/Music/MainMenuSong.mp3");
	m_CurrentLevel = Level::MAIN_MENU;
	auto menu = PrefabCreator::CreateMainMenu();
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("MainMenu");
	scene.Add(menu);
	scene.Start();



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
	case Level::LEVEL2:
		dae::SceneManager::GetInstance().DestroyScene("Level2");
		break;
	case Level::LEVEL3:
		dae::SceneManager::GetInstance().DestroyScene("Level3");
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
	ServiceLocator::GetSoundSystem().StopAll();
	ServiceLocator::GetSoundSystem().play("Resources/Music/GamOverSong.mp3");

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
	case Level::LEVEL2:
		CreateLevel2();
		break;
	case Level::LEVEL3:
		CreateLevel3();
		break;
	case Level::GAME_OVER:
		CreateGameOver();
		break;
	default:
		CreateMainMenu();
		break;
	}
}

void BurgerTime::CreateLevel2()
{
	ServiceLocator::GetSoundSystem().StopAll();
	ServiceLocator::GetSoundSystem().play("Resources/Music/LEVEL2.mp3");

	m_CurrentLevel = Level::LEVEL2;
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("Level2");
	CreateLevel("Resources/Level_2.json", &scene);
	scene.Start();
}

void BurgerTime::CreateLevel3()
{
	ServiceLocator::GetSoundSystem().StopAll();
	ServiceLocator::GetSoundSystem().play("Resources/Music/LEVEL3.mp3");

	m_CurrentLevel = Level::LEVEL3;
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("Level3");
	CreateLevel("Resources/Level_3.json", &scene);
	scene.Start();
}

