#include "BurgerTimePCH.h"
#include "BurgerTime.h"
#include "ResourceManager.h"
void BurgerTime::Initialize()
{
	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Data/");
}

