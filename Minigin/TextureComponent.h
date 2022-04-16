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
		std::shared_ptr<Texture2D> GetTexture() { return m_Texture; }
		void SetTexture(std::shared_ptr<Texture2D> newTexture);
		virtual void Start() override;
		void Render() const override;
		void Update() override;
		void LateUpdate() override;

	private:
		std::shared_ptr<Texture2D> m_Texture;
		RenderComponent* m_pRenderComponent;
	};
}


