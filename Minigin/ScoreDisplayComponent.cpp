#include "MiniginPCH.h"
#include "ScoreDisplayComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
dae::ScoreDisplayComponent::ScoreDisplayComponent(std::string newString) : m_BaseString{newString} {}

void dae::ScoreDisplayComponent::Start()
{
	m_pParent->GetComponent<TextComponent>()->SetText(m_BaseString + std::to_string(m_Score));
}

void dae::ScoreDisplayComponent::onNotify(const BaseComponent*, EventType event, EventArgs* args)
{
	ScoreArgs* sargs = static_cast<ScoreArgs*>(args);
	m_Score += sargs->scoreIncrease;
	switch (event)
	{
	case dae::EventType::SCORE_INCREASE:
		m_pParent->GetComponent<TextComponent>()->SetText(m_BaseString + std::to_string(m_Score));
		break;
	}
}

