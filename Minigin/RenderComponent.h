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
		void FixedUpdate() override;
		void SetData(Texture2D* newData);

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		Texture2D* m_DataToRender;
	};



}


