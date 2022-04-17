#pragma once
#include "BaseComponent.h"

namespace dae {
	class TillingComponent : public BaseComponent
	{
	public:
		TillingComponent(int steps, int whiteSpace, bool isVertical = true);
		void Render() const override {};
		void Update() override {};
		void LateUpdate() override;
		virtual void Start() override;
		
		int GetTileAmount() { return m_Steps; };
		int GetWhiteSpace() { return m_WhiteSpace; };
		bool IsVertical() { return m_IsVertical; }

	private:
		int m_Steps;
		int m_WhiteSpace;
		bool m_IsVertical;

	};
}
