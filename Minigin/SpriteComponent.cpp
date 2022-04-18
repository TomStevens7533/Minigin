#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Texture2D.h"
#include <SDL.h>
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"


dae::SpriteComponent::SpriteComponent(std::string path, int collAmount, int rowAmount, float timeFrame)
	: m_TotalCol{ collAmount }, m_TotalRow{ rowAmount }, m_TimeFrame{ timeFrame }
{
	m_SpriteTexture = dae::ResourceManager::GetInstance().LoadTexture(path);
	int width, height, access;
	uint32_t format;
	SDL_QueryTexture(m_SpriteTexture->GetSDLTexture(), &format, &access, &width, &height);

	m_widthPerCell = width / collAmount;
	m_HeightPerCell = height / rowAmount;


}
dae::SpriteComponent::~SpriteComponent()
{

}

bool dae::SpriteComponent::AddAnimation(const std::string key,int starCol, int startRow, int endCol, int endRow)
{

	if ((starCol < m_TotalCol && endCol < m_TotalCol) && (startRow < m_TotalRow && endRow < m_TotalRow)) {
		SDL_Rect rt;
		rt.x = m_widthPerCell * starCol;
		rt.y = m_HeightPerCell * startRow;
		rt.w = m_widthPerCell * (endCol - starCol);
		rt.h = m_HeightPerCell * (endRow - startRow);

		//Get part of fullTexture
		SDL_Renderer* renderer = dae::Renderer::GetInstance().GetSDLRenderer();
		SDL_Texture* spriteTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rt.w, rt.h);
		SDL_SetRenderTarget(renderer, spriteTexture);
		SDL_RenderCopy(renderer, m_SpriteTexture->GetSDLTexture(), &rt, NULL);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_GetError();


		//Change to not use pointer and new 
		auto it = m_AnimationMap.emplace(std::piecewise_construct, 
			std::make_tuple(key), 
			std::make_tuple(spriteTexture, m_widthPerCell, m_HeightPerCell, m_TimeFrame));

		if (m_ActiveAnimation == nullptr) {
			m_ActiveAnimation = &it.first->second;
		}
		return it.second;
	}
	else {
		//Place assert if row idx is out of bounds
		return false;
	}

}
void dae::SpriteComponent::SetActiveAnimation(std::string key)
{
	m_ActiveAnimation = &m_AnimationMap.at(key);
}

glm::vec2 dae::SpriteComponent::GetCurrentAnimDimensions()
{
	return m_ActiveAnimation->GetCurrentDimensions();
}

void dae::SpriteComponent::Render() const
{
	m_ActiveAnimation->Render(m_pParent->GetTransform(), m_IsFlipped);
}

void dae::SpriteComponent::Update()
{
	m_ActiveAnimation->Update();
}

