#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <string>

namespace dae {

	struct ScoreArgs : public EventArgs
	{
		int scoreIncrease;
	};

	class ScoreDisplayComponent final : public BaseComponent, public Observer {
	public:
		ScoreDisplayComponent(std::string newString);
		~ScoreDisplayComponent() = default;

		virtual void Start() override;
		virtual void Update() override {};
		virtual void LateUpdate() override {};
		virtual void Render() const override {};
		virtual void onNotify(const BaseComponent* entity, EventType event, EventArgs* args) override;

	private:
		int m_Score{0};
		std::string m_BaseString{};

	};
}