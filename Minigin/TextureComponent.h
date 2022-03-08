#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "RenderComponent.h"

namespace dae {
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent();
		~TextureComponent();

	
		void SetTexture(const std::string& filename);
		void SetPosition(const glm::vec2& pos);

		void Render() const override;
		void Update() override;
		void LateUpdate() override;

	private:
		std::shared_ptr<Texture2D> m_Texture;
		std::unique_ptr<RenderComponent> m_RenderComponent;
	};
}


