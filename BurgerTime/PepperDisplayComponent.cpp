#include "MiniginPCH.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "PepperDisplayComponent.h"
#include "AttackComponent.h"
#include "EventType.h"

Burger::PepperDisplayComponent::PepperDisplayComponent(std::string newString) : m_BaseString{ newString }
{
}

void Burger::PepperDisplayComponent::Start()
{
	m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString);
}

void Burger::PepperDisplayComponent::onNotify(const BaseComponent*, int event, dae::EventArgs* args)
{
	//Unsafe
	AttackArgs* hargs = static_cast<AttackArgs*>(args);
	switch (event)
	{
	case Burger::PepperEvent::PEPPER_FIRED:
		m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString + std::to_string(hargs->pepperShots));
		break;
	}
}
