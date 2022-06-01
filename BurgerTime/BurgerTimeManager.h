#pragma once
#include "Singleton.h"
#include "Observer.h"

namespace Burger { class BurgerTime; }
namespace dae {
	class BaseComponent; struct EventArgs;
}

enum class Gamemode {
	COOP,
	PVP,
	SOLO
};

class GameManager : public dae::Singleton<GameManager>, public dae::Observer {
public:
	void SetGamemode(Gamemode newMode);
	void SetBurgerGame(Burger::BurgerTime* pgame);
	void ResetCurrentLevel();
	void GoToNextLevel();

	virtual void onNotify(const dae::BaseComponent* entity, int event, dae::EventArgs* args = nullptr) override;
private:
	Burger::BurgerTime* m_pGame = nullptr;
	Gamemode m_CurrentGamemode = Gamemode::SOLO;
};