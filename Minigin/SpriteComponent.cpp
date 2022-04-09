#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Texture2D.h"
#include <SDL.h>
#include "Renderer.h"
#include "ResourceManager.h"

dae::SpriteComponent::SpriteComponent(int startCol, int startRow, int colAmount, int rowAmount, std::shared_ptr<Texture2D> fullTexture)
{
	int width, height, access;
	uint32_t format;
	//Querry texture to get basic information out of it;
	SDL_QueryTexture(fullTexture->GetSDLTexture(), &format, &access, &width, &height);
	//fill SDL Rect based on that info

	m_MaxFrames = colAmount * rowAmount;

	SDL_Rect rt;
	rt.x = startCol * width;
	rt.y = startRow * height;
	rt.w = colAmount * width;
	rt.h = rowAmount * height;

	SDL_Texture* spriteTexture = nullptr;
	//Get part of fullTexture
	SDL_RenderCopy(dae::Renderer::GetInstance().GetSDLRenderer(),spriteTexture, &rt, NULL);
	SDL_GetError();

	//Create unique ptr based upon that
	//m_SpriteTexture = std::make_unique<Texture2D>(spriteTexture);
}

dae::SpriteComponent::SpriteComponent(std::string path, int, int)
{
	//m_SpriteTexture = std::make_unique<Texture2D>(dae::ResourceManager::GetInstance().LoadTexture(path));
}
dae::SpriteComponent::~SpriteComponent()
{

}



