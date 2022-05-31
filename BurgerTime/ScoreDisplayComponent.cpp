#include "MiniginPCH.h"
#include "ScoreDisplayComponent.h"
#include "GameObject.h"
#include "EventType.h"
#include "TextComponent.h"
Burger::ScoreDisplayComponent::ScoreDisplayComponent(std::string newString) : m_BaseString{newString} {}

void Burger::ScoreDisplayComponent::Start()
{
	m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString + std::to_string(m_Score));
}

void Burger::ScoreDisplayComponent::onNotify(const BaseComponent*, int event, dae::EventArgs* args)
{
	switch (event)
	{
	case Burger::PepperEvent::SCORE_INCREASE:
		ScoreArgs* sargs = static_cast<ScoreArgs*>(args);
		m_Score += sargs->scoreIncrease;
		m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString + std::to_string(m_Score));
		break;
	}
}

