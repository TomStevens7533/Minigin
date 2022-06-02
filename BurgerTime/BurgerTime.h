#pragma once

namespace dae {
	class Scene;
}
namespace Burger {

	class BurgerTime {
	public:
		void Initialize();
		void CreateLevel1();
		void LoadStage(unsigned int level);
		unsigned int GetCurrentStage();
	private:
		void CreateLevel(const std::string& path, dae::Scene* currScene);
	private:
		unsigned int m_currentLevelIdx{};
	};
}

