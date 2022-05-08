#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <limits.h>
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"

namespace dae {



	TextureComponent::TextureComponent(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}
	void TextureComponent::SetTexture(std::shared_ptr<Texture2D> newTexture)
	{
		assert(m_pParent);
		m_Texture.reset();
		m_Texture = newTexture;
		RenderComponent* renderComponent = (m_pParent->AddOrGetComponent<dae::RenderComponent>());

		renderComponent->SetData(m_Texture.get());

	}

	void TextureComponent::TileTexture(int steps, int whiteSpace, bool isVertical /*= true*/)
	{
		SDL_Renderer* renderer = dae::Renderer::GetInstance().GetSDLRenderer();
		Uint32 pixelFormat;
		int height;
		int width;
		SDL_QueryTexture(m_Texture->GetSDLTexture(), &pixelFormat, NULL, &width, &height);
		SDL_Texture* bigTexture;

		if (isVertical)
			bigTexture = SDL_CreateTexture(renderer, pixelFormat, SDL_TEXTUREACCESS_TARGET, width, (height + whiteSpace) * steps);
		else
			bigTexture = SDL_CreateTexture(renderer, pixelFormat, SDL_TEXTUREACCESS_TARGET, (width + whiteSpace) * steps, height);

		SDL_SetRenderTarget(renderer, bigTexture);
		//Go over steps to increase texture
		for (int i = 0; i < (steps); i++)
		{
			SDL_Rect dstRect;

			//Tile vertically or horizontally
			if (isVertical) {
				dstRect.x = 0;
				dstRect.y = static_cast<int>(((height)*i) + (whiteSpace * i));
			}
			else {
				dstRect.x = static_cast<int>(((width)*i) + (whiteSpace * i));
				dstRect.y = 0;
			}
			dstRect.w = width;
			dstRect.h = height;
			SDL_RenderCopy(renderer, m_Texture->GetSDLTexture(), NULL, &dstRect);

		}
		SDL_SetRenderTarget(renderer, NULL);
		//Set new texture as texture of textureComponent;
		std::shared_ptr<Texture2D> newTex = std::make_shared<Texture2D>(bigTexture);
		SetTexture(newTex);
	}

	glm::vec2 TextureComponent::GetDimensions()
	{
		return m_Texture->GetDimensions();
	}

	void TextureComponent::Start()
	{
		RenderComponent* renderComponent = (m_pParent->AddOrGetComponent<dae::RenderComponent>());
		renderComponent->SetData(m_Texture.get());
	}
	TextureComponent::~TextureComponent()
	{
		m_Texture.reset();
	}
	void TextureComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

};


