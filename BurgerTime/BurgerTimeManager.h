#pragma once
#include "Singleton.h"
#include "Observer.h"
#include "Subject.h"
#include "BurgerStructs.h"

namespace Burger { class BurgerTime; }
namespace dae {
	class BaseComponent; struct EventArgs;
}



class GameManager : public dae::Singleton<GameManager>, public dae::Observer, public dae::Subject {
public:
	void SetGamemode(Gamemode newMode);
	void SetBurgerGame(Burger::BurgerTime* pgame);
	void ResetCurrentLevel();
	void GoToNextLevel();
	void ResetScore();
	std::vector<int> ReadScore();

	Gamemode GetCurrentGamemode() const { return m_CurrentGamemode; }

	void AddToScore(int score);
	int GetScore();

	int GetPepperShots() const;
	void SubtractPepperShots();

	int GetLives() const;
	void SubtractLive();

	void onNotify(const dae::BaseComponent* entity, int event, dae::EventArgs* args = nullptr) override;
	void SetNewLevelInfo(LevelInfo info);

private:
	Burger::BurgerTime* m_pGame = nullptr;
	Gamemode m_CurrentGamemode = Gamemode::SOLO;
	const std::string m_HighScoreSavePath = "BurgerTimeHighScores.sav";
	LevelInfo m_CurrentInfo;
	LevelInfo m_ResetInfo;
	int m_Score;
	bool m_IsLoadingLevel = false;
};