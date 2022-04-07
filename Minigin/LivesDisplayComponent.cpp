#include "MiniginPCH.h"
#include "LivesDisplayComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "HealthComponent.h"

void dae::LivesDisplayComponent::onNotify(const BaseComponent*, EventType event, EventArgs* args)
{
	//GetComponent
	HealthArgs* hargs = static_cast<HealthArgs*>(args);
	switch (event)
	{
	case dae::EventType::ENTITY_DIED:
		m_pParent->GetComponent<TextComponent>()->SetText(std::to_string(hargs->lives));
		break;
	case dae::EventType::HEALTH_SET:
		m_pParent->GetComponent<TextComponent>()->SetText(std::to_string(hargs->lives));
		break;
	}
}



