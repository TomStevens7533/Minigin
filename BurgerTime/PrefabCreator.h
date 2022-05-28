#pragma once
#include "BurgerStructs.h"
#include "SceneObject.h"
#include <memory>

namespace Burger {
	class PrefabCreator {
	public:
		static const std::shared_ptr<dae::SceneObject> CreatePlayerPrefab(point pos);
	private:
		static int m_PlayerCount;
	};



}