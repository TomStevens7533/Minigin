#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae {
	class RenderComponent;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::string& filename);
		~TextureComponent();

	
		void SetTexture(const std::string& filename);
		std::shared_ptr<Texture2D> GetTexture() { return m_Texture; }
		void SetTexture(std::shared_ptr<Texture2D> newTexture);
		void TileTexture(int steps, int whiteSpace, bool isVertical = true);
		glm::vec2 GetDimensions();


		virtual void Start() override;
		void Render() const override {};
		void Update() override {};
		void FixedUpdate() override {};

	private:
		std::shared_ptr<Texture2D> m_Texture;
	};
}


