#include "MiniginPCH.h"
#include "AttackComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include <iostream>
#include "SpriteComponent.h"
#include "Scene.h"
#include "Time.h"

void dae::AttackComponent::Render() const
{

}

void dae::AttackComponent::Update()
{
	if (m_IsFiring) {
		if (m_CurrentPeperTime < m_MaxPepperTime) {
			m_CurrentPeperTime += dae::Time::GetInstance().GetDeltaTime();
			std::cout << m_pWeaponGameobject->RelativePositionToParent().x <<
				m_pWeaponGameobject->RelativePositionToParent().y << std::endl;
		}
		else {
			m_CurrentPeperTime = 0.f;
			GetAttachedGameObject()->RemoveChild(m_pWeaponGameobject);
			m_IsFiring = false;
		}
	}


	

}

void dae::AttackComponent::LateUpdate()
{

}

void dae::AttackComponent::Start()
{
	//Create pepper shot gameobject
	m_pWeaponGameobject = std::make_shared<dae::GameObject>();
	auto TexComp = std::make_shared<TextureComponent>("pepperShot.png");
	auto boxComp = std::make_shared<BoxColliderComponent>("Shot");
	m_pWeaponGameobject->AddComponent<TextureComponent>(TexComp);
	m_pWeaponGameobject->AddComponent<BoxColliderComponent>(boxComp);
}

void dae::AttackComponent::Fire()
{
	if (m_IsFiring == false) {
		std::cout << "Fire\n";
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

	}

}
