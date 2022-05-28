#include "BurgerTimePCH.h"
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "BurgerTime.h"

int main(int, char* []) {
	dae::Minigin engine;
	engine.Initialize();

	Burger::BurgerTime game;
	game.Initialize();

	engine.Run();
	return 0;
}