#include "MiniginPCH.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "PepperDisplayComponent.h"
#include "AttackComponent.h"

dae::PepperDisplayComponent::PepperDisplayComponent(std::string newString) : m_BaseString{ newString }
{
}

void dae::PepperDisplayComponent::Start()
{
	m_pParent->GetComponent<TextComponent>()->SetText(m_BaseString);
}

void dae::PepperDisplayComponent::onNotify(const BaseComponent*, int event, EventArgs* args)
{
	//Unsafe
	AttackArgs* hargs = static_cast<AttackArgs*>(args);
	switch (event)
	{
	case dae::PepperEvent::PEPPER_FIRED:
		m_pParent->GetComponent<TextComponent>()->SetText(m_BaseString + std::to_string(hargs->pepperShots));
		break;
	}
}
