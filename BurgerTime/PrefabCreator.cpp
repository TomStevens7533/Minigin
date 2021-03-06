#pragma warning(disable:4201)

#include "PrefabCreator.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "PetterPepperComponent.h"
#include "MovementComponent.h"
#include "AttackComponent.h"
#include "TextureComponent.h"
#include "BunBehaviour.h"
#include "EnemyBehaviourComponent.h"
#include "EnemySpawning.h"
#include "TextComponent.h"
#include "ScoreDisplayComponent.h"
#include "ResourceManager.h"
#include "PepperDisplayComponent.h"
#include "LivesDisplayComponent.h"
#include "FInalBurgerComponent.h"
#include "MainMenuComponent.h"
#include "Command.cpp"
#include "GameOverComponent.h"

using namespace Burger;

int Burger::PrefabCreator::m_PlayerCount = 0;

std::shared_ptr<dae::GameObject> PrefabCreator::CreateEnemySpawner(std::vector<point> spawnPoint, std::map<EnemyType, EnemySpawnInfo>& enemyMap)
{
	auto spawner = std::make_shared<dae::GameObject>();
	spawner->SetName("StageEnemySpawner");
	auto EnemyComp = std::make_shared<EnemySpawnComponent>(spawnPoint, enemyMap);
	spawner->AddComponent<EnemySpawnComponent>(EnemyComp);
	return spawner;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreateEggEnemy(point pos, int m_Score)
{
	auto eggEnemy = std::make_shared<dae::GameObject>();
	auto spriteComponent = std::make_shared<dae::SpriteComponent>("SpiteSheet.png", 15, 11, 0.3f);
	auto boxCollider = std::make_shared<dae::BoxColliderComponent>("Enemy", 5);
	auto movementComp = std::make_shared<MovementComponent>(40.f);
	auto hotdogg = std::make_shared<EnemyBehaviourComponent>("Player", EnemyType::EGG, m_Score);



	spriteComponent->AddAnimation("MoveSide", 2, 6, 4, 7);
	spriteComponent->AddAnimation("MoveForward", 0, 6, 2, 7);
	spriteComponent->AddAnimation("MoveBackwards", 4, 6, 6, 7);
	spriteComponent->AddAnimation("Fried", 4, 7, 6, 8);
	spriteComponent->AddAnimation("Death", 0, 7, 4, 8);

	eggEnemy->AddComponent<dae::SpriteComponent>(spriteComponent);
	eggEnemy->AddComponent<dae::BoxColliderComponent>(boxCollider);
	eggEnemy->AddComponent<MovementComponent>(movementComp);
	eggEnemy->AddComponent<EnemyBehaviourComponent>(hotdogg);

	eggEnemy->SetPosition(pos.x, pos.y);
	return eggEnemy;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreateSpikey(point pos, int m_Score)
{
	auto spikey = std::make_shared<dae::GameObject>();

	auto spriteComponent = std::make_shared<dae::SpriteComponent>("SpiteSheet.png", 15, 11, 0.3f);
	auto boxCollider = std::make_shared<dae::BoxColliderComponent>("Enemy", 5);
	auto movementComp = std::make_shared<MovementComponent>(50.f);
	auto hotdogg = std::make_shared<EnemyBehaviourComponent>("Player", EnemyType::SPIKE, m_Score);



	spriteComponent->AddAnimation("MoveSide", 2, 4, 4, 5);
	spriteComponent->AddAnimation("MoveForward", 0, 4, 2, 5);
	spriteComponent->AddAnimation("MoveBackwards", 4, 4, 6, 5);
	spriteComponent->AddAnimation("Fried", 4, 4, 6, 5);
	spriteComponent->AddAnimation("Death", 0, 4, 4, 5);

	spikey->AddComponent<dae::SpriteComponent>(spriteComponent);
	spikey->AddComponent<dae::BoxColliderComponent>(boxCollider);
	spikey->AddComponent<MovementComponent>(movementComp);
	spikey->AddComponent<EnemyBehaviourComponent>(hotdogg);

	spikey->SetPosition(pos.x, pos.y);
	return spikey;
}
std::shared_ptr<dae::GameObject> PrefabCreator::CreatWorstEnemyrPrefab(point pos, int m_Score)
{
	auto hotdoggGo = std::make_shared<dae::GameObject>();
	auto spriteComponent = std::make_shared<dae::SpriteComponent>("SpiteSheet.png", 15, 11, 0.3f);
	auto boxCollider = std::make_shared<dae::BoxColliderComponent>("Enemy", 5);
	auto movementComp = std::make_shared<MovementComponent>(40.f);
	auto hotdogg = std::make_shared<EnemyBehaviourComponent>("Player", EnemyType::WORST, m_Score);


	spriteComponent->AddAnimation("MoveSide", 2, 2, 4, 3);
	spriteComponent->AddAnimation("MoveForward", 0, 2, 2, 3);
	spriteComponent->AddAnimation("MoveBackwards", 4, 2, 6, 3);
	spriteComponent->AddAnimation("Fried", 4, 3, 6, 4);
	spriteComponent->AddAnimation("Death", 0, 3, 4, 4);

	hotdoggGo->AddComponent<dae::SpriteComponent>(spriteComponent);
	hotdoggGo->AddComponent<dae::BoxColliderComponent>(boxCollider);
	hotdoggGo->AddComponent<MovementComponent>(movementComp);
	hotdoggGo->AddComponent<EnemyBehaviourComponent>(hotdogg);

	hotdoggGo->SetPosition(pos.x, pos.y);
	return hotdoggGo;
}
std::shared_ptr<dae::GameObject> PrefabCreator::CreateScoreUI(point pos)
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22);
	glm::vec3 color = { 255, 0, 0 };
	auto scoreDisplayGo = std::make_shared<dae::GameObject>();
	auto textComp = std::make_shared<dae::TextComponent>("0", font, color);
	auto scoreDisplayComponent = std::make_shared<ScoreDisplayComponent>("Score: ");
	scoreDisplayGo->SetPosition(pos.x, pos.y);
	scoreDisplayGo->AddComponent<dae::TextComponent>(textComp);
	scoreDisplayGo->AddComponent<ScoreDisplayComponent>(scoreDisplayComponent);
	return scoreDisplayGo;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreatePepperUI(point pos)
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22);
	glm::vec3 color = { 255, 0, 0 };
	auto pepperDisplayGO = std::make_shared<dae::GameObject>();
	auto textComp = std::make_shared<dae::TextComponent>(" ", font, color);
	auto pepperDisplaycomp = std::make_shared<PepperDisplayComponent>("Pepper: ");
	pepperDisplayGO->AddComponent<dae::TextComponent>(textComp);
	pepperDisplayGO->AddComponent<PepperDisplayComponent>(pepperDisplaycomp);
	pepperDisplayGO->SetPosition(pos.x, pos.y);
	return pepperDisplayGO;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreateLivesUI(point pos)
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22);
	glm::vec3 color = { 255, 0, 0 };
	auto liveDisplayGO = std::make_shared<dae::GameObject>();
	auto textComp = std::make_shared<dae::TextComponent>(" ", font, color);
	auto liveDisplaycomp = std::make_shared<LivesDisplayComponent>("Lives: ");

	liveDisplayGO->AddComponent<dae::TextComponent>(textComp);
	liveDisplayGO->AddComponent<LivesDisplayComponent>(liveDisplaycomp);
	liveDisplayGO->SetPosition(pos.x, pos.y);
	return liveDisplayGO;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreateMainMenu()
{
	auto menu = std::make_shared<dae::GameObject>();
	auto menuComp = std::make_shared<MainMenuComp>();
	menu->AddComponent<MainMenuComp>(menuComp);
	return menu;
}
std::shared_ptr<dae::GameObject> PrefabCreator::CreateGameOver()
{
	auto menu = std::make_shared<dae::GameObject>();
	auto menuComp = std::make_shared<GameoverComp>();
	menu->AddComponent<GameoverComp>(menuComp);
	return menu;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreatePlayableWorstPrefab(point pos, int score, int playerID)
{
	auto hotdoggGo = std::make_shared<dae::GameObject>();
	auto spriteComponent = std::make_shared<dae::SpriteComponent>("SpiteSheet.png", 15, 11, 0.3f);
	auto boxCollider = std::make_shared<dae::BoxColliderComponent>("Enemy", 5);
	auto movementComp = std::make_shared<MovementComponent>(40.f);
	auto inputComponent = std::make_shared<dae::InputComponent>(playerID);
	MovementComponent* pMove = movementComp.get();

	inputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_LEFT, 37, new MoveLeftEnterCommand(pMove), dae::KeyState::DOWN);
	inputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveRightEnterCommand(pMove), dae::KeyState::DOWN);
	inputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_UP, 38, new MoveUpEnterCommand(pMove), dae::KeyState::DOWN);
	inputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_DOWN, 40, new MoveDownEnterCommand(pMove), dae::KeyState::DOWN);


	inputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_LEFT, 37, new MoveLeftExitCommand(pMove), dae::KeyState::RELEASED);
	inputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_RIGHT, 39, new MoveRightExitCommand(pMove), dae::KeyState::RELEASED);
	inputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_UP, 38, new MoveUpExitCommand(pMove), dae::KeyState::RELEASED);
	inputComponent->AddCommand(dae::ControllerButton::GAMEPAD_DPAD_DOWN, 40, new MoveDownExitCommand(pMove), dae::KeyState::RELEASED);

	//Make playable
	auto hotdogg = std::make_shared<EnemyBehaviourComponent>("Player", EnemyType::WORST, score, true);


	spriteComponent->AddAnimation("MoveSide", 2, 2, 4, 3);
	spriteComponent->AddAnimation("MoveForward", 0, 2, 2, 3);
	spriteComponent->AddAnimation("MoveBackwards", 4, 2, 6, 3);
	spriteComponent->AddAnimation("Fried", 4, 3, 6, 4);
	spriteComponent->AddAnimation("Death", 0, 3, 4, 4);

	hotdoggGo->AddComponent<dae::SpriteComponent>(spriteComponent);
	hotdoggGo->AddComponent<dae::BoxColliderComponent>(boxCollider);
	hotdoggGo->AddComponent<MovementComponent>(movementComp);
	hotdoggGo->AddComponent<EnemyBehaviourComponent>(hotdogg);
	hotdoggGo->AddComponent<dae::InputComponent>(inputComponent);


	hotdoggGo->SetPosition(pos.x, pos.y);
	++m_PlayerCount;
	return hotdoggGo;
}


std::shared_ptr<dae::GameObject> PrefabCreator::CreatePlatformPrefab(point pos, int tilling)
{
	
	auto goFloor = std::make_shared<dae::GameObject>();
	auto texComp = std::make_shared<dae::TextureComponent>("Walkable.png");
	auto goBoxColl = std::make_shared<dae::BoxColliderComponent>("Floor", 4);

	goFloor->AddComponent<dae::TextureComponent>(texComp);
	goFloor->AddComponent<BoxColliderComponent>(goBoxColl);
	texComp->TileTexture(tilling, 0, false);

	goFloor->SetPosition(pos.x, pos.y);
	return goFloor;
}



std::shared_ptr<dae::GameObject> PrefabCreator::CreatePlayerPrefab(point pos, int playerID)
{
	auto PeterPepper = std::make_shared<dae::GameObject>();
	PeterPepper->SetName("Player");
	auto inputComponent = std::make_shared<dae::InputComponent>(playerID);
	auto spriteComponent = std::make_shared<dae::SpriteComponent>("SpiteSheet.png", 15, 11, 0.15f);
	auto peterPepperComp = std::make_shared<PetterPepperComponent>();
	auto movementComp = std::make_shared<MovementComponent>(70.f);
	auto attackComp = std::make_shared<AttackComponent>();

	auto boxCollider = std::make_shared<dae::BoxColliderComponent>("Pepper", 5);

	spriteComponent->AddAnimation("MoveForward", 6, 0, 9, 1);
	spriteComponent->AddAnimation("Move", 3, 0, 6, 1);
	spriteComponent->AddAnimation("MoveBackwards", 0, 0, 3, 1);
	spriteComponent->AddAnimation("Death", 6, 1, 9, 2);
	spriteComponent->AddAnimation("Victory", 0, 1, 5, 2);
	spriteComponent->AddAnimation("Idle", 0, 0, 1, 1);




	PeterPepper->AddComponent<AttackComponent>(attackComp);
	PeterPepper->AddComponent<dae::InputComponent>(inputComponent);
	PeterPepper->AddComponent<dae::SpriteComponent>(spriteComponent);
	PeterPepper->AddComponent<PetterPepperComponent>(peterPepperComp);
	PeterPepper->AddComponent<MovementComponent>(movementComp);
	PeterPepper->AddComponent<dae::BoxColliderComponent >(boxCollider);



	PeterPepper->SetPosition(pos.x, pos.y);

	++m_PlayerCount;


	return PeterPepper;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreateLadderPrefab(point pos, int tilling)
{
	auto goLadder = std::make_shared<dae::GameObject>();
	auto texComp = std::make_shared<dae::TextureComponent>("ladder.png");
	auto goBoxColl = std::make_shared<dae::BoxColliderComponent>("Ladder", 6);


	goLadder->AddComponent<dae::TextureComponent>(texComp);
	goLadder->AddComponent<dae::BoxColliderComponent>(goBoxColl);
	texComp->TileTexture(tilling, 5);

	goLadder->SetPosition(pos.x, pos.y);

	return goLadder;

}
// Burger pieces
std::shared_ptr<dae::GameObject> PrefabCreator::CreatTopBurgerPrefab(point pos)
{
	auto goBurgerPiece = std::make_shared<dae::GameObject>();
	goBurgerPiece->SetName("Bun");
	auto TexComp = std::make_shared<dae::TextureComponent>("TopBun.png");
	auto boxComp = std::make_shared<dae::BoxColliderComponent>("Bun", 2);
	auto bunComp = std::make_shared<BunBehaviour>();
	goBurgerPiece->AddComponent<dae::BoxColliderComponent>(boxComp);
	goBurgerPiece->AddComponent<dae::TextureComponent>(TexComp);
	goBurgerPiece->AddComponent<BunBehaviour>(bunComp);

	goBurgerPiece->SetPosition(pos.x, pos.y);
	return goBurgerPiece;
}
std::shared_ptr<dae::GameObject> PrefabCreator::CreatLettuceBurgerPrefab(point pos)
{

	auto goBurgerPiece = std::make_shared<dae::GameObject>();
	goBurgerPiece->SetName("Bun");
	auto TexComp = std::make_shared<dae::TextureComponent>("Lettuce.png");
	auto boxComp = std::make_shared<dae::BoxColliderComponent>("Bun", 2);
	auto bunComp = std::make_shared<BunBehaviour>();
	goBurgerPiece->AddComponent<dae::BoxColliderComponent>(boxComp);
	goBurgerPiece->AddComponent<dae::TextureComponent>(TexComp);
	goBurgerPiece->AddComponent<BunBehaviour>(bunComp);

	goBurgerPiece->SetPosition(pos.x, pos.y);
	return goBurgerPiece;
}



std::shared_ptr<dae::GameObject> PrefabCreator::CreatTomatoBurgerPrefab(point pos)
{
	auto goBurgerPiece = std::make_shared<dae::GameObject>();
	goBurgerPiece->SetName("Bun");
	auto TexComp = std::make_shared<dae::TextureComponent>("Tomato.png");
	auto boxComp = std::make_shared<dae::BoxColliderComponent>("Bun", 2);
	auto bunComp = std::make_shared<BunBehaviour>();
	goBurgerPiece->AddComponent<dae::BoxColliderComponent>(boxComp);
	goBurgerPiece->AddComponent<dae::TextureComponent>(TexComp);
	goBurgerPiece->AddComponent<BunBehaviour>(bunComp);

	goBurgerPiece->SetPosition(pos.x, pos.y);
	return goBurgerPiece;
}
std::shared_ptr<dae::GameObject> PrefabCreator::CreatLowerBurgerPrefab(point pos)
{
	auto goBurgerPiece = std::make_shared<dae::GameObject>();
	goBurgerPiece->SetName("Bun");
	auto TexComp = std::make_shared<dae::TextureComponent>("LowerBun.png");
	auto boxComp = std::make_shared<dae::BoxColliderComponent>("Bun", 2);
	auto bunComp = std::make_shared<BunBehaviour>();
	goBurgerPiece->AddComponent<dae::BoxColliderComponent>(boxComp);
	goBurgerPiece->AddComponent<dae::TextureComponent>(TexComp);
	goBurgerPiece->AddComponent<BunBehaviour>(bunComp);

	goBurgerPiece->SetPosition(pos.x, pos.y);
	return goBurgerPiece;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreatBurgerCathcherPrefab(point pos)
{
	auto goBurgerPiece = std::make_shared<dae::GameObject>();
	auto TexComp = std::make_shared<dae::TextureComponent>("BurgerCatcher.png");
	auto boxComp = std::make_shared<dae::BoxColliderComponent>("BunEnd", 2);
	auto bunComp = std::make_shared<FinalBurgerComponent>(4);

	goBurgerPiece->AddComponent<dae::BoxColliderComponent>(boxComp);
	goBurgerPiece->AddComponent<dae::TextureComponent>(TexComp);
	goBurgerPiece->AddComponent<FinalBurgerComponent>(bunComp);

	goBurgerPiece->SetPosition(pos.x, pos.y);
	return goBurgerPiece;
}

