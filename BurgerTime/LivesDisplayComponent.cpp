#include "MiniginPCH.h"
#include "LivesDisplayComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "EventType.h"
#include "BurgerEvents.h"
#include "Scene.h"
#include "PetterPepperComponent.h"
#include "BurgerTimeManager.h"

Burger::LivesDisplayComponent::LivesDisplayComponent(std::string newString) : m_BaseString{newString} 
{
	
}


void Burger::LivesDisplayComponent::Start()
{
	//Find all petter pepper go and add itself as observer
	auto inf = GetAttachedGameObject()->GetScene()->GetGameObjectsWithTag("Player");

	for (size_t i = 0; i < inf.size(); i++)
		inf[i]->GetComponent<PetterPepperComponent>()->addObserver(this);

	//set text
	m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString + std::to_string(m_CurrentLives));
}

void Burger::LivesDisplayComponent::onNotify(const BaseComponent*, int event, dae::EventArgs* args)
{
	//GetComponent
	switch (event)
	{
	case Burger::PepperEvent::HEALTH_DECREASE:
		--m_CurrentLives;
		m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString + std::to_string(m_CurrentLives));
		GameManager::GetInstance().ResetCurrentLevel();
		break;
	}
}



