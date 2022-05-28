#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae {

	class LivesDisplayComponent final : public BaseComponent, public Observer {
	public:
		LivesDisplayComponent(std::string newString);
		~LivesDisplayComponent() = default;

		virtual void Start() override{};
		virtual void Update() override {};
		virtual void LateUpdate() override {};
		virtual void Render() const override {};
		virtual void onNotify(const BaseComponent* entity, int event, EventArgs* args) override;

	private:
		std::string m_BaseString{};
	};
}