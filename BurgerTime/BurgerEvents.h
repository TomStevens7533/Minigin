#pragma once
#include "Observer.h"
#include "BurgerStructs.h"
struct EnemyArgs : public dae::EventArgs
{
	EnemyType type;
	int points{};
};

struct ScoreArgs : public dae::EventArgs
{
	int scoreIncrease;
};
struct HealthArgs : public dae::EventArgs
{
	int health;
	int lives;
};