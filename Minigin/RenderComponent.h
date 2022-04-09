#pragma once

#include "BaseComponent.h"
#include "Texture2D.h"
#include <glm/glm.hpp>

namespace dae {
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent();
		~RenderComponent();

		virtual void Start() override {};
		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		void SetData(std::shared_ptr<void> newData);

	private:
		std::shared_ptr<void> m_DataToRender;
	};



}


