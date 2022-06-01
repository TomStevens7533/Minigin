#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace Burger {

	class LivesDisplayComponent final : public dae::BaseComponent, public dae::Observer {
	public:
		LivesDisplayComponent(std::string newString);
		~LivesDisplayComponent() = default;

		virtual void Start() override;
		virtual void Update() override {};
		virtual void LateUpdate() override {};
		virtual void Render() const override {};
		virtual void onNotify(const BaseComponent* entity, int event, dae::EventArgs* args) override;

	private:
		std::string m_BaseString{};
		int m_CurrentLives = 5;
	};
}