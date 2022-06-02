#pragma once
#include "Singleton.h"
#include "Observer.h"
#include "Subject.h"

namespace Burger { class BurgerTime; }
namespace dae {
	class BaseComponent; struct EventArgs;
}

enum class Gamemode {
	COOP,
	PVP,
	SOLO
};
struct LevelInfo
{
	int MaxLives;
	int MaxPepper;
	int BunWinCoun;
};

class GameManager : public dae::Singleton<GameManager>, public dae::Observer, public dae::Subject {
public:
	void SetGamemode(Gamemode newMode);
	void SetBurgerGame(Burger::BurgerTime* pgame);
	void ResetCurrentLevel();
	void GoToNextLevel();

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
	
	LevelInfo m_CurrentInfo;
	int m_Score;

	bool m_IsLoadingLevel = true;
};