#include "MiniginPCH.h"
#include "ScoreDisplayComponent.h"
#include "GameObject.h"
#include "BurgerEvents.h"
#include "EventType.h"
#include "TextComponent.h"
#include "BunBehaviour.h"
#include "EnemySpawning.h"
Burger::ScoreDisplayComponent::ScoreDisplayComponent(std::string newString) : m_BaseString{newString} {}

void Burger::ScoreDisplayComponent::Start()
{

	//Find all petter pepper go and add itself as observer
	auto inf = GetAttachedGameObject()->GetScene()->GetGameObjectsWithTag("Bun");

	for (size_t i = 0; i < inf.size(); i++)
		inf[i]->GetComponent<BunBehaviour>()->addObserver(this);


	inf = GetAttachedGameObject()->GetScene()->GetGameObjectsWithTag("StageEnemySpawner");

	for (size_t i = 0; i < inf.size(); i++)
		inf[i]->GetComponent<EnemySpawnComponent>()->addObserver(this);


	m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString + std::to_string(m_Score));
}

void Burger::ScoreDisplayComponent::onNotify(const BaseComponent*, int event, dae::EventArgs* args)
{
	switch (event)
	{
	case Burger::PepperEvent::SCORE_INCREASE:
	{
		ScoreArgs* sargs = static_cast<ScoreArgs*>(args);
		m_Score += sargs->scoreIncrease;
		m_pParent->GetComponent<dae::TextComponent>()->SetText(m_BaseString + std::to_string(m_Score));
		break;
	}
	
	}

}

