#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <string>

namespace Burger {

	class ScoreDisplayComponent final : public dae::BaseComponent, public dae::Observer {
	public:
		ScoreDisplayComponent(std::string newString);
		~ScoreDisplayComponent() = default;

		virtual void Start() override;
		virtual void Update() override {};
		virtual void LateUpdate() override {};
		virtual void Render() const override {};
		virtual void onNotify(const BaseComponent* entity, int event, dae::EventArgs* args) override;



	private:
		int m_Score{0};
		std::string m_BaseString{};

	};
}