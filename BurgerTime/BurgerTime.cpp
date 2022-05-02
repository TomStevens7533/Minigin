#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"

int main(int, char* []) {
	dae::Minigin engine;
	engine.Run();
	return 0;
}