#pragma once
#include "BaseComponent.h"
#include <string>
#include "Observer.h"

namespace dae {

	class PepperDisplayComponent final : public BaseComponent, public Observer {
	public:
		PepperDisplayComponent(std::string newString);
		~PepperDisplayComponent() = default;

		virtual void Start() override;
		virtual void Update() override {};
		virtual void LateUpdate() override {};
		virtual void Render() const override {};
		virtual void onNotify(const BaseComponent* entity, int event, EventArgs* args) override;

	private:
		int m_Lives{};
		std::string m_BaseString{};

	};
}