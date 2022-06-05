#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace Burger {

	class ScoreDisplayComponent final : public dae::BaseComponent, public dae::Observer {
	public:
		ScoreDisplayComponent(std::string newString);
		~ScoreDisplayComponent() = default;

		virtual void Start() override;
		virtual void Update() override {};
		virtual void FixedUpdate() override {};
		virtual void Render() const override {};
		virtual void onNotify(const BaseComponent* entity, int event, dae::EventArgs* args) override;

		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

	private:
		std::string m_BaseString{};

	};
}