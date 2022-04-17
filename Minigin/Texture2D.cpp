#include "MiniginPCH.h"
#include "Texture2D.h"


dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

glm::vec2 dae::Texture2D::GetDimensions()
{
	Uint32 pixelFormat;
	int height;
	int width;
	SDL_QueryTexture(m_Texture, &pixelFormat, NULL, &width, &height);
	return glm::vec2(width, height);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
