#include "BurgerTimeManager.h"
#include "BurgerTime.h"
#include "BaseComponent.h"
#include "Observer.h"
#include "EventType.h"
#include "InputManager.h"
#include <iostream>
#include <fstream>

void GameManager::SetGamemode(Gamemode newMode)
{
	m_CurrentGamemode = newMode;
}

void GameManager::SetBurgerGame(Burger::BurgerTime* pgame)
{
	m_pGame = pgame;
}

void GameManager::ResetCurrentLevel()
{
	if (m_pGame != nullptr) {
		m_pGame->RemoveStage(m_pGame->GetCurrentStage());
		dae::InputManager::GetInstance().RemoveAllPlayers();
		m_CurrentInfo.MaxPepper = m_ResetInfo.MaxPepper;
		m_CurrentInfo.BunWinCoun = m_ResetInfo.BunWinCoun;
		m_pGame->LoadStage(m_pGame->GetCurrentStage());
	}
}

void GameManager::GoToNextLevel()
{
	if (m_pGame != nullptr) {
		m_IsLoadingLevel = true;
		m_pGame->RemoveStage(m_pGame->GetCurrentStage());
		dae::InputManager::GetInstance().RemoveAllPlayers();
		m_pGame->LoadNextStage(m_pGame->GetCurrentStage());
	}
}

void GameManager::ResetScore()
{
	//save score to file
	if (m_Score != 0) {
		std::fstream oStream{ m_HighScoreSavePath, std::fstream::app |std::ios::out | std::ios::binary };

		if (oStream.is_open())
		{
			oStream.write(reinterpret_cast<const char*>(&m_Score), sizeof(int));
		}
		oStream.close();
	}
	m_Score = 0;
}

std::vector<int> GameManager::ReadScore()
{
	std::vector<int> m_LoadedScores;
	int score;
	std::ifstream iSteam(m_HighScoreSavePath, std::ios::in | std::ios::binary);
	if (iSteam.is_open()) {

		while (!iSteam.eof())
		{
			iSteam.read((char*)&score, sizeof(int));
			if (!iSteam.good()){
				//input failure, leave the loop
				break;
			}
			m_LoadedScores.push_back(score);
		}
	}
	iSteam.close();
	std::reverse(m_LoadedScores.begin(), m_LoadedScores.end());
	return m_LoadedScores;
}

void GameManager::AddToScore(int score)
{
	m_Score += score;

}

int GameManager::GetScore()
{
	return m_Score;
}

int GameManager::GetPepperShots() const
{
	return m_CurrentInfo.MaxPepper;
}

void GameManager::SubtractPepperShots()
{
	--m_CurrentInfo.MaxPepper;
}

int GameManager::GetLives() const
{
	return m_CurrentInfo.MaxLives;
}

void GameManager::SubtractLive()
{
	--m_CurrentInfo.MaxLives;
	if (m_CurrentInfo.MaxLives <= 0) {
		m_IsLoadingLevel = true;
		m_pGame->RemoveStage(m_pGame->GetCurrentStage());
		m_pGame->LoadStage(Burger::Level::GAME_OVER);
	}
}

void GameManager::onNotify(const dae::BaseComponent* entity, int event, dae::EventArgs* args /*= nullptr*/)
{
	switch (event)
	{
	case Burger::PepperEvent::BURGER_COMPLETE:
		if (m_CurrentInfo.BunWinCoun > 0) {
			--m_CurrentInfo.BunWinCoun;
		}
		if(m_CurrentInfo.BunWinCoun <= 0) {
			notify(nullptr, Burger::PepperEvent::LEVEL_COMPLETE, nullptr);
		}

	default:
		break;
	}
}

void GameManager::SetNewLevelInfo(LevelInfo info)
{
	if (m_IsLoadingLevel) {
		m_CurrentInfo = info;
		m_ResetInfo = m_CurrentInfo;
		m_IsLoadingLevel = false;
	}
}

