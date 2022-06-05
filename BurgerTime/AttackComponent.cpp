#include "MiniginPCH.h"
#include "AttackComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include <iostream>
#include "SpriteComponent.h"
#include "Scene.h"
#include "DeltaTime.h"
#include "EventType.h"
#include "BurgerTimeManager.h"
#include "ServiceLocator.h"

int Burger::AttackComponent::m_PepperShots = 5;

using namespace dae;
void Burger::AttackComponent::Render() const
{
	
}

void Burger::AttackComponent::Update()
{
	if (m_IsFiring) {
		if (m_CurrentPeperTime < m_MaxPepperTime) {
			m_CurrentPeperTime += dae::Time::GetInstance().GetDeltaTime();
		}
		else {
			m_CurrentPeperTime = 0.f;
			m_pPepperCollider->DisableCollider();
			GetAttachedGameObject()->RemoveChild(m_pWeaponGameobject);
			m_IsFiring = false;
		}
	}


	

}

void Burger::AttackComponent::FixedUpdate()
{

}

void Burger::AttackComponent::Start()
{
	//Create pepper shot gameobject
	m_pWeaponGameobject = std::make_shared<dae::GameObject>();
	std::shared_ptr<TextureComponent> TexComp = std::make_shared<TextureComponent>("pepperShot.png");
	std::shared_ptr<dae::BoxColliderComponent> boxComp = std::make_shared<dae::BoxColliderComponent>("Shot");
	m_pWeaponGameobject->AddComponent<TextureComponent>(TexComp);
	m_pWeaponGameobject->AddComponent<dae::BoxColliderComponent>(boxComp);
	m_pPepperCollider = m_pWeaponGameobject->GetComponent<dae::BoxColliderComponent>();

	AttackArgs args;
	args.pepperShots = m_PepperShots;
	notify(this, PepperEvent::PEPPER_FIRED, &args);
}

void Burger::AttackComponent::Fire()
{
	if (m_IsFiring == false && GameManager::GetInstance().GetPepperShots() > 0) {


		ServiceLocator::GetSoundSystem().play("Resources/FX/Pepper.mp3");

		GameManager::GetInstance().SubtractPepperShots();
		SpriteComponent* comp = GetAttachedGameObject()->GetComponent<SpriteComponent>();
		bool isFlipped = comp->GetFLipState();
		glm::vec2 animDim = comp->GetCurrentAnimDimensions();
		m_IsFiring = true;
		glm::vec3 pos;

		if (isFlipped)
			pos.x += animDim.x;
		else
			pos.x -= animDim.x * 2.f;
		pos.y -= animDim.y / 2.f;

		m_pWeaponGameobject->GetTransform().SetPosition(pos.x, pos.y, pos.z);
		GetAttachedGameObject()->AddChild(m_pWeaponGameobject);
		m_pPepperCollider->EnableCollider();



		AttackArgs args;
		args.pepperShots = m_PepperShots;
		notify(this, PepperEvent::PEPPER_FIRED, &args);


	}

}


