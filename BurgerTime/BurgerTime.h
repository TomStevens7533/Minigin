#pragma once

namespace dae {
	class Scene;
}
namespace Burger {
	enum class Level
	{
		MAIN_MENU,
		LEVEL1,
		LEVEL2,
		LEVEL3,
		GAME_OVER

	};


	class BurgerTime {
	public:
		void Initialize();
		void CreateMainMenu();
		void CreateLevel1();
		void CreateLevel2();
		void CreateLevel3();

		void CreateGameOver();

		void LoadNextStage(Level level);
		void LoadStage(Level level);

		void RemoveStage(Level level);
		Level GetCurrentStage();
	private:
		void CreateLevel(const std::string& path, dae::Scene* currScene);
	private:
		Level m_CurrentLevel{Level::MAIN_MENU};
	};
}

