#include "BurgerTimeManager.h"
#include "BurgerTime.h"
#include "BaseComponent.h"
#include "Observer.h"

void GameManager::SetGamemode(Gamemode newMode)
{

}

void GameManager::SetBurgerGame(Burger::BurgerTime* pgame)
{
	m_pGame = pgame;
}

void GameManager::ResetCurrentLevel()
{
	if (m_pGame != nullptr) {
		m_pGame->LoadStage(m_pGame->GetCurrentStage());
	}
}

void GameManager::GoToNextLevel()
{

}

void GameManager::onNotify(const dae::BaseComponent* entity, int event, dae::EventArgs* args /*= nullptr*/)
{
}

