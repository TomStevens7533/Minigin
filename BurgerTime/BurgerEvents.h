#pragma once
#include "Observer.h"
#include "BurgerStructs.h"
struct EnemyArgs final  : public dae::EventArgs
{
	EnemyType type;
	int points{};
};

struct ScoreArgs final  : public dae::EventArgs
{
	int scoreIncrease;
};
struct HealthArgs final  : public dae::EventArgs
{
	int health;
	int lives;
};