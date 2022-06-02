#pragma once
#include "BaseComponent.h"
namespace Burger {
	class MainMenuComp : public dae::BaseComponent
	{
	public:
		MainMenuComp() = default;
		~MainMenuComp() = default;
		void Render() const override ;
		void Update() override { };
		void LateUpdate() override {};
		virtual void Start() override {};

		MainMenuComp(const MainMenuComp& other) = delete;
		MainMenuComp(MainMenuComp&& other) = delete;
		MainMenuComp& operator=(const MainMenuComp& other) = delete;
		MainMenuComp& operator=(MainMenuComp&& other) = delete;
	private:

	};
}
