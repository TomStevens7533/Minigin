#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae {
	class RenderComponent;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent();
		~TextureComponent();

	
		void SetTexture(const std::string& filename);
		virtual void Start() override;
		void Render() const override;
		void Update() override;
		void LateUpdate() override;

	private:
		std::shared_ptr<Texture2D> m_Texture;
		std::shared_ptr<RenderComponent> m_RenderComponent;
	};
}


