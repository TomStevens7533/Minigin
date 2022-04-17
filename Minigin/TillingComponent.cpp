#include "MiniginPCH.h"
#include "GameObject.h"
#include "TillingComponent.h"
#include "TextureComponent.h"
#include "Renderer.h"

dae::TillingComponent::TillingComponent(int steps, int whiteSpace, bool isVertical) : 
	m_Steps{steps}, m_WhiteSpace{whiteSpace}, m_IsVertical{isVertical}
{

}

void dae::TillingComponent::LateUpdate()
{

}

void dae::TillingComponent::Start()
{
	TextureComponent* texComp = m_pParent->GetComponent<TextureComponent>();

	if (texComp != nullptr) {
		SDL_Renderer* renderer = dae::Renderer::GetInstance().GetSDLRenderer();
		Uint32 pixelFormat;
		int height;
		int width;
		SDL_QueryTexture(texComp->GetTexture()->GetSDLTexture(), &pixelFormat, NULL, &width, &height);
		SDL_Texture* bigTexture;

		if (m_IsVertical)
			bigTexture = SDL_CreateTexture(renderer, pixelFormat, SDL_TEXTUREACCESS_TARGET, width, (height + m_WhiteSpace) * m_Steps);
		else
			bigTexture = SDL_CreateTexture(renderer, pixelFormat, SDL_TEXTUREACCESS_TARGET, (width + m_WhiteSpace) * m_Steps, height);

		SDL_SetRenderTarget(renderer, bigTexture);
		//Go over steps to increase texture
		for (size_t i = 0; i < (m_Steps); i++)
		{
			SDL_Rect dstRect;

			//Tile vertically or horizontally
			if (m_IsVertical) {
				dstRect.x = 0;
				dstRect.y = static_cast<int>(((height)*i) + (m_WhiteSpace * i));
			}
			else {
				dstRect.x = static_cast<int>(((width)*i) + (m_WhiteSpace * i));
				dstRect.y = 0;
			}
			dstRect.w = width;
			dstRect.h = height;
			SDL_RenderCopy(renderer, texComp->GetTexture()->GetSDLTexture(), NULL, &dstRect);

		}
		SDL_SetRenderTarget(renderer, NULL);
		//Set new texture as texture of textureComponent;
		std::shared_ptr<Texture2D> newTex = std::make_shared<Texture2D>(bigTexture);
		texComp->SetTexture(newTex);
	}
	
}

