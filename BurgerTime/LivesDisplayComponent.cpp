#include "MiniginPCH.h"
#include "LivesDisplayComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "EventType.h"
#include "BurgerEvents.h"

Burger::LivesDisplayComponent::LivesDisplayComponent(std::string newString) : m_BaseString{newString} {}


void Burger::LivesDisplayComponent::onNotify(const BaseComponent*, int event, dae::EventArgs* args)
{
	//GetComponent
	HealthArgs* hargs = static_cast<HealthArgs*>(args);
	switch (event)
	{
	case Burger::PepperEvent::ENTITY_DIED:
		m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString + std::to_string(hargs->lives));
		break;
	case Burger::PepperEvent::HEALTH_SET:
		m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString + std::to_string(hargs->lives));
		break;
	}
}



