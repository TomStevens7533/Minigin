#include "PrefabCreator.h"
#include "HealthComponent.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "PetterPepperComponent.h"
#include "MovementComponent.h"
#include "AttackComponent.h"
#include "TextureComponent.h"
#include "BunBehaviour.h"
#include "AIBehaviourComponent.h"
#include "EnemySpawning.h"

using namespace Burger;



std::shared_ptr<dae::GameObject> PrefabCreator::CreateEnemySpawner(std::vector<point> spawnPoint, std::map<std::string, EnemySpawnInfo>& enemyMap)
{
	auto spawner = std::make_shared<dae::GameObject>();
	auto EnemyComp = std::make_shared<EnemySpawnComponent>(spawnPoint, enemyMap);
	spawner->AddComponent<EnemySpawnComponent>(EnemyComp);
	return spawner;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreateEggEnemy(point pos)
{
	auto eggEnemy = std::make_shared<dae::GameObject>();
	auto spriteComponent = std::make_shared<dae::SpriteComponent>("SpiteSheet.png", 15, 11, 0.3f);
	auto boxCollider = std::make_shared<dae::BoxColliderComponent>("Enemy", 5);
	auto movementComp = std::make_shared<MovementComponent>(40.f);
	auto hotdogg = std::make_shared<AIBehaviourComponent>("Pepper", "egg");



	spriteComponent->AddAnimation("MoveSide", 2, 6, 4, 7);
	spriteComponent->AddAnimation("MoveForward", 0, 6, 2, 7);
	spriteComponent->AddAnimation("MoveBackwards", 4, 6, 6, 7);
	spriteComponent->AddAnimation("Fried", 4, 7, 6, 8);
	spriteComponent->AddAnimation("Death", 0, 7, 4, 8);

	eggEnemy->AddComponent<dae::SpriteComponent>(spriteComponent);
	eggEnemy->AddComponent<dae::BoxColliderComponent>(boxCollider);
	eggEnemy->AddComponent<MovementComponent>(movementComp);
	eggEnemy->AddComponent<AIBehaviourComponent>(hotdogg);

	eggEnemy->SetPosition(pos.x, pos.y);
	return eggEnemy;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreateSpikey(point pos)
{
	auto spikey = std::make_shared<dae::GameObject>();

	auto spriteComponent = std::make_shared<dae::SpriteComponent>("SpiteSheet.png", 15, 11, 0.3f);
	auto boxCollider = std::make_shared<dae::BoxColliderComponent>("Enemy", 5);
	auto movementComp = std::make_shared<MovementComponent>(50.f);
	auto hotdogg = std::make_shared<AIBehaviourComponent>("Pepper", "Spike");



	spriteComponent->AddAnimation("MoveSide", 2, 4, 4, 5);
	spriteComponent->AddAnimation("MoveForward", 0, 4, 2, 5);
	spriteComponent->AddAnimation("MoveBackwards", 4, 4, 6, 5);
	spriteComponent->AddAnimation("Fried", 4, 4, 6, 5);
	spriteComponent->AddAnimation("Death", 0, 4, 4, 5);

	spikey->AddComponent<dae::SpriteComponent>(spriteComponent);
	spikey->AddComponent<dae::BoxColliderComponent>(boxCollider);
	spikey->AddComponent<MovementComponent>(movementComp);
	spikey->AddComponent<AIBehaviourComponent>(hotdogg);

	spikey->SetPosition(pos.x, pos.y);
	return spikey;
}

int Burger::PrefabCreator::m_PlayerCount = 0;

std::shared_ptr<dae::GameObject> PrefabCreator::CreatWorstEnemyrPrefab(point pos)
{
	auto hotdoggGo = std::make_shared<dae::GameObject>();
	auto spriteComponent = std::make_shared<dae::SpriteComponent>("SpiteSheet.png", 15, 11, 0.3f);
	auto boxCollider = std::make_shared<dae::BoxColliderComponent>("Enemy", 5);
	auto movementComp = std::make_shared<MovementComponent>(40.f);
	auto hotdogg = std::make_shared<AIBehaviourComponent>("Pepper", "worst");


	spriteComponent->AddAnimation("MoveSide", 2, 2, 4, 3);
	spriteComponent->AddAnimation("MoveForward", 0, 2, 2, 3);
	spriteComponent->AddAnimation("MoveBackwards", 4, 2, 6, 3);
	spriteComponent->AddAnimation("Fried", 4, 3, 6, 4);
	spriteComponent->AddAnimation("Death", 0, 3, 4, 4);

	hotdoggGo->AddComponent<dae::SpriteComponent>(spriteComponent);
	hotdoggGo->AddComponent<dae::BoxColliderComponent>(boxCollider);
	hotdoggGo->AddComponent<MovementComponent>(movementComp);
	hotdoggGo->AddComponent<AIBehaviourComponent>(hotdogg);

	hotdoggGo->SetPosition(pos.x, pos.y);
	return hotdoggGo;
}
std::shared_ptr<dae::GameObject> PrefabCreator::CreatePlatformPrefab(point pos, int tilling)
{
	
	auto goFloor = std::make_shared<dae::GameObject>();
	auto texComp = std::make_shared<dae::TextureComponent>("Walkable.png");
	auto goBoxColl = std::make_shared<dae::BoxColliderComponent>(texComp->GetDimensions(), "Floor", 2);

	goFloor->AddComponent<dae::TextureComponent>(texComp);
	goFloor->AddComponent<BoxColliderComponent>(goBoxColl);
	texComp->TileTexture(tilling, 0, false);

	goFloor->SetPosition(pos.x, pos.y);
	return goFloor;
}



std::shared_ptr<dae::GameObject> PrefabCreator::CreatePlayerPrefab(point pos)
{
	auto PeterPepper = std::make_shared<dae::GameObject>();
	auto healthComponent = std::make_shared<HealthComponent>();
	auto inputComponent = std::make_shared<dae::InputComponent>(m_PlayerCount);
	auto spriteComponent = std::make_shared<dae::SpriteComponent>("SpiteSheet.png", 15, 11, 0.3f);
	auto peterPepperComp = std::make_shared<PetterPepperComponent>();
	auto movementComp = std::make_shared<MovementComponent>(70.f);
	auto attackComp = std::make_shared<AttackComponent>();
	auto boxCollider = std::make_shared<dae::BoxColliderComponent>("Pepper", 5);

	///*	attackComp->addObserver(pepperDisplaycomp);
	//	healthComponent->addObserver(liveDisplaycomp)*/;
	//
	//
	//	m_PlayerCount++;
	//	//Anims


	spriteComponent->AddAnimation("MoveForward", 6, 0, 9, 1);
	spriteComponent->AddAnimation("Move", 3, 0, 6, 1);
	spriteComponent->AddAnimation("MoveBackwards", 0, 0, 3, 1);
	spriteComponent->AddAnimation("Death", 6, 1, 9, 2);


	PeterPepper->AddComponent<AttackComponent>(attackComp);
	PeterPepper->AddComponent<HealthComponent>(healthComponent);
	PeterPepper->AddComponent<dae::InputComponent>(inputComponent);
	PeterPepper->AddComponent<dae::SpriteComponent>(spriteComponent);
	PeterPepper->AddComponent<PetterPepperComponent>(peterPepperComp);
	PeterPepper->AddComponent<MovementComponent>(movementComp);
	PeterPepper->AddComponent <dae::BoxColliderComponent >(boxCollider);


	PeterPepper->SetPosition(pos.x, pos.y);



	return PeterPepper;
}

std::shared_ptr<dae::GameObject> PrefabCreator::CreateLadderPrefab(point pos, int tilling)
{
	auto goLadder = std::make_shared<dae::GameObject>();
	auto texComp = std::make_shared<dae::TextureComponent>("ladder.png");
	auto goBoxColl = std::make_shared<dae::BoxColliderComponent>(texComp->GetDimensions(), "Ladder", 6);


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
	auto TexComp = std::make_shared<dae::TextureComponent>("TopBun.png");
	auto boxComp = std::make_shared<dae::BoxColliderComponent>("Bun");
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
	auto TexComp = std::make_shared<dae::TextureComponent>("Lettuce.png");
	auto boxComp = std::make_shared<dae::BoxColliderComponent>("Bun");
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
	auto TexComp = std::make_shared<dae::TextureComponent>("Tomato.png");
	auto boxComp = std::make_shared<dae::BoxColliderComponent>("Bun");
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
	auto TexComp = std::make_shared<dae::TextureComponent>("LowerBun.png");
	auto boxComp = std::make_shared<dae::BoxColliderComponent>("Bun");
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
	auto boxComp = std::make_shared<dae::BoxColliderComponent>("BunEnd");
	auto bunComp = std::make_shared<BunBehaviour>();
	goBurgerPiece->AddComponent<dae::BoxColliderComponent>(boxComp);
	goBurgerPiece->AddComponent<dae::TextureComponent>(TexComp);
	goBurgerPiece->AddComponent<BunBehaviour>(bunComp);

	goBurgerPiece->SetPosition(pos.x, pos.y);
	return goBurgerPiece;
}

