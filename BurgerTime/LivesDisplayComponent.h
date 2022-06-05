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
		virtual void FixedUpdate() override {};
		virtual void Render() const override {};
		virtual void onNotify(const BaseComponent* entity, int event, dae::EventArgs* args) override;


		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& other) = delete;

	private:
		std::string m_BaseString{};
	};
}