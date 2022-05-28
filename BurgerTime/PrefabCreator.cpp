#include "PrefabCreator.h"
#include "glm/glm.hpp"
#include "GameObject.h"
#include "HealthComponent.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "PetterPepperComponent.h"
#include "MovementComponent.h"
#include "AttackComponent.h"

using namespace Burger;

int Burger::PrefabCreator::m_PlayerCount = 0;

void PrefabCreator::CreatePlayerPrefab(point pos)
{
	//auto PeterPepper = std::make_shared<dae::GameObject>();
	auto healthComponent = std::make_shared<HealthComponent>();
	auto inputComponent = std::make_shared<dae::InputComponent>(m_PlayerCount);
	auto spriteComponent = std::make_shared<dae::SpriteComponent>("SpiteSheet.png", 15, 11, 0.3f);
	auto peterPepperComp = std::make_shared<PetterPepperComponent>();
	auto movementComp = std::make_shared<MovementComponent>(70.f);
	auto attackComp = std::make_shared<AttackComponent>();
///*	attackComp->addObserver(pepperDisplaycomp);
//	healthComponent->addObserver(liveDisplaycomp)*/;
//
//	auto boxCollider = std::make_shared<dae::BoxColliderComponent>("Pepper", 5);
//
//	m_PlayerCount++;
//	//Anims
//	spriteComponent->AddAnimation("MoveForward", 6, 0, 9, 1);
//	spriteComponent->AddAnimation("Move", 3, 0, 6, 1);
//	spriteComponent->AddAnimation("MoveBackwards", 0, 0, 3, 1);
//	spriteComponent->AddAnimation("Death", 6, 1, 9, 2);
//
//
//	PeterPepper->AddComponent<AttackComponent>(attackComp);
//	PeterPepper->AddComponent<HealthComponent>(healthComponent);
//	PeterPepper->AddComponent<dae::InputComponent>(inputComponent);
//	PeterPepper->AddComponent<dae::SpriteComponent>(spriteComponent);
//	PeterPepper->AddComponent<PetterPepperComponent>(peterPepperComp);
//	PeterPepper->AddComponent<MovementComponent>(movementComp);
//	PeterPepper->AddComponent <dae::BoxColliderComponent > (boxCollider);
//
//
//	PeterPepper->SetPosition(pos.x, pos.y);
//



}
