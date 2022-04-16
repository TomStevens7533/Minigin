#include "MiniginPCH.h"
#include "LadderComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Renderer.h"

dae::LadderComponent::LadderComponent(int steps, int whiteSpace) : m_heightSteps{steps}, m_WhiteSpace{whiteSpace}
{

}

void dae::LadderComponent::LateUpdate()
{

}

void dae::LadderComponent::Start()
{
	TextureComponent* texComp = m_pParent->GetComponent<TextureComponent>();
	SDL_Renderer* renderer = dae::Renderer::GetInstance().GetSDLRenderer();
	Uint32 pixelFormat;
	int height;
	int width;
	SDL_QueryTexture(texComp->GetTexture()->GetSDLTexture(), &pixelFormat, NULL, &width, &height);
	SDL_Texture* bigTexture = SDL_CreateTexture(renderer, pixelFormat, SDL_TEXTUREACCESS_TARGET, (height + m_WhiteSpace) * m_heightSteps, width);
	SDL_SetRenderTarget(renderer, bigTexture);
	//Go over steps to increase texture
	for (size_t i = 1; i < m_heightSteps + 1; i++)
	{
		SDL_Rect dstRect;
		dstRect.x = 0;
		dstRect.y = static_cast<int>((height+ m_WhiteSpace)*i);
		dstRect.w = width;
		dstRect.h = height;

		SDL_RenderCopy(renderer, texComp->GetTexture()->GetSDLTexture(), NULL,  &dstRect);

	}
	SDL_SetRenderTarget(renderer, NULL);
	//Set new texture as texture of textureComponent;
	std::shared_ptr<Texture2D> newTex = std::make_shared<Texture2D>(bigTexture);
	texComp->SetTexture(newTex);
}

