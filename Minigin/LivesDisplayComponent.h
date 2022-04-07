#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae {

	class LivesDisplayComponent final : public BaseComponent, public Observer {
	public:
		LivesDisplayComponent() = default;
		~LivesDisplayComponent() = default;

		virtual void Update() override {};
		virtual void LateUpdate() override {};
		virtual void Render() const override {};
		virtual void onNotify(const BaseComponent* entity, EventType event, EventArgs* args) override;

	private:
		int m_Lives{};

	};
}