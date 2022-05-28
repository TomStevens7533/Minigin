#pragma once
#include "BurgerStructs.h"

namespace Burger {
	class PrefabCreator {
	public:
		static void CreatePlayerPrefab(point pos);
	private:
		static int m_PlayerCount;
	};



}