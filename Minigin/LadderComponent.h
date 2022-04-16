#pragma once
#include "BaseComponent.h"

namespace dae {
	class LadderComponent : public BaseComponent
	{
	public:
		LadderComponent(int steps, int whiteSpace);
		void Render() const override {};
		void Update() override {};
		void LateUpdate() override;
		virtual void Start() override;
	private:
		std::string m_Path;
		int m_heightSteps;
		int m_WhiteSpace;
	};
}
