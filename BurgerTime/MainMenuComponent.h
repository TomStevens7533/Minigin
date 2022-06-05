#pragma once
#include "BaseComponent.h"
#include "BurgerStructs.h"
#include <vector>
namespace Burger {
	class MainMenuComp final : public dae::BaseComponent
	{
	public:
		MainMenuComp() = default;
		~MainMenuComp() = default;
		void Render() const override ;
		void Update() override { };
		void FixedUpdate() override {};
		virtual void Start() override;

		MainMenuComp(const MainMenuComp& other) = delete;
		MainMenuComp(MainMenuComp&& other) = delete;
		MainMenuComp& operator=(const MainMenuComp& other) = delete;
		MainMenuComp& operator=(MainMenuComp&& other) = delete;
	private:
	private:
		Gamemode m_SelectedGamemode = Gamemode::SOLO;
		std::vector<int> m_HighScoreVec{};

	};
}
