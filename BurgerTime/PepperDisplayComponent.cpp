#include "MiniginPCH.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "PepperDisplayComponent.h"
#include "EventType.h"
#include "AttackComponent.h"

Burger::PepperDisplayComponent::PepperDisplayComponent(std::string newString) : m_BaseString{ newString }
{

}

void Burger::PepperDisplayComponent::Start()
{
	m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString);

	//Find all petter pepper go and add itself as observer
	auto inf = GetAttachedGameObject()->GetScene()->GetGameObjectsWithTag("Player");

	for (size_t i = 0; i < inf.size(); i++)
		inf[i]->GetComponent<AttackComponent>()->addObserver(this);
}

void Burger::PepperDisplayComponent::onNotify(const BaseComponent*, int event, dae::EventArgs* args)
{
	//Unsafe
	AttackArgs* hargs;
	switch (event)
	{
	case Burger::PepperEvent::PEPPER_FIRED:
		hargs = static_cast<AttackArgs*>(args);
		m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString + std::to_string(hargs->pepperShots));
		break;
	}
}
