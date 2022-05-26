#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "BurgerTime.h"

int main(int, char* []) {
	BurgerTime game;
	game.Initialize();

	dae::Minigin engine;
	engine.Run();
	return 0;
}