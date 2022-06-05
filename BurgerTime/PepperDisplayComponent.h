#pragma once
#include "BaseComponent.h"
#include <string>
#include "Observer.h"

namespace Burger {

	class PepperDisplayComponent final : public dae::BaseComponent, public dae::Observer {
	public:
		PepperDisplayComponent(std::string newString);
		~PepperDisplayComponent() = default;

		virtual void Start() override;
		virtual void Update() override {};
		virtual void FixedUpdate() override {};
		virtual void Render() const override {};
		virtual void onNotify(const BaseComponent* entity, int event, dae::EventArgs* args) override;

	private:
		int m_PepperShots{};
		std::string m_BaseString{};

	};
}