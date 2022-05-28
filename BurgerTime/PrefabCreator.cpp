#include "PrefabCreator.h"
#include "GameObject.h"

using namespace Burger;

void PrefabCreator::CreatePlayerPrefab()
{
	auto PeterPepper = std::make_shared<dae::GameObject>();
	auto healthComponent = std::make_shared<HealthComponent>();
	auto inputComponent = std::make_shared<InputComponent>(static_cast<int>(i));
	auto spriteComponent = std::make_shared<SpriteComponent>("SpiteSheet.png", 15, 11, 0.3f);
	auto peterPepperComp = std::make_shared<PetterPepperComponent>();
	auto movementComp = std::make_shared<MovementComponent>(70.f);
	auto attackComp = std::make_shared<AttackComponent>();
	attackComp->addObserver(pepperDisplaycomp);
	healthComponent->addObserver(liveDisplaycomp);

	auto boxCollider = std::make_shared<BoxColliderComponent>("Pepper", 5);


	//Anims
	spriteComponent->AddAnimation("MoveForward", 6, 0, 9, 1);
	spriteComponent->AddAnimation("Move", 3, 0, 6, 1);
	spriteComponent->AddAnimation("MoveBackwards", 0, 0, 3, 1);
	spriteComponent->AddAnimation("Death", 6, 1, 9, 2);


	PeterPepper->AddComponent<AttackComponent>(attackComp);
	PeterPepper->AddComponent<HealthComponent>(healthComponent);
	PeterPepper->AddComponent<InputComponent>(inputComponent);
	PeterPepper->AddComponent<SpriteComponent>(spriteComponent);
	PeterPepper->AddComponent<PetterPepperComponent>(peterPepperComp);
	PeterPepper->AddComponent<MovementComponent>(movementComp);
	PeterPepper->AddComponent<BoxColliderComponent>(boxCollider);


	glm::vec2 pos = posVec[i];
	PeterPepper->SetPosition(pos.x, pos.y);


	scene->Add(PeterPepper);

	//UI translate
	uiPos.y += 40.f;




}
