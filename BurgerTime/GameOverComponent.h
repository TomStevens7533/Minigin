#pragma once
#include "BaseComponent.h"
namespace Burger {
	class GameoverComp final : public dae::BaseComponent
	{
	public:
		GameoverComp() = default;
		~GameoverComp() = default;
		void Render() const override;
		void Update() override { };
		void LateUpdate() override {};
		virtual void Start() override {};

		GameoverComp(const GameoverComp& other) = delete;
		GameoverComp(GameoverComp&& other) = delete;
		GameoverComp& operator=(const GameoverComp& other) = delete;
		GameoverComp& operator=(GameoverComp&& other) = delete;
	private:

	};
}
