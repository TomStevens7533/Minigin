#include "MiniginPCH.h"
#include "Animation.h"
#include "Time.h"
#include <SDL.h>
#include "Renderer.h"
#include "Texture2D.h"

namespace dae {

	Animation::Animation(SDL_Texture* animTexture, int widthPerCell, int heightPerCell, float m_TimeFrame)
		: m_FrameTime{ m_TimeFrame }
	{
		int width, height, access;
		uint32_t format;
		SDL_QueryTexture(animTexture, &format, &access, &width, &height);

		m_Cols = static_cast<int>(std::ceil(width / (widthPerCell))); //Get Amount of cells X;
		m_Rows = static_cast<int>(std::ceil(height / (heightPerCell))); //Get Amount of cells Y;

		m_TotalFrames = m_Cols * m_Rows;

		//Fill in width and height into rect to draw
		m_RectToDraw.width = static_cast<float>(widthPerCell);
		m_RectToDraw.height = static_cast<float>(heightPerCell);

		//Fill in texture
		m_AnimationSprite = std::make_shared<Texture2D>(animTexture);
	}

	Animation::Animation(const Animation& lhs)
	{
		m_AnimationSprite = lhs.m_AnimationSprite;

		m_Backwards = lhs.m_Backwards;
		m_Cols = lhs.m_Cols;
		m_Rows = lhs.m_Rows;
		m_RectToDraw = lhs.m_RectToDraw;
		m_TotalFrames = lhs.m_TotalFrames;
		m_FrameTime = lhs.m_FrameTime;
	}

	Animation::~Animation()
	{
	}

	void Animation::Update()
	{
		m_AccumulatedTime += dae::Time::GetInstance().GetDeltaTime();

		if (m_AccumulatedTime > m_FrameTime)
		{

			if (!m_Backwards)
				++m_CurrentFrame %= m_TotalFrames;
			else --m_CurrentFrame %= m_TotalFrames;
			m_AccumulatedTime -= m_FrameTime;

		}

		int col{ m_CurrentFrame % m_Cols };//col van het current frame
		int row{ m_CurrentFrame / m_Cols };//row van het current frame

		m_RectToDraw.x = m_RectToDraw.width * (float)col;
		m_RectToDraw.y = m_RectToDraw.height * (float)row;
	}

	void Animation::Render(Transform tr, bool isFlip) const
	{
		SDL_Rect dstRect{};
		dstRect.x = static_cast<int>(std::round(tr.GetPosition().x));
		dstRect.y = static_cast<int>(std::round(tr.GetPosition().y));
		dstRect.w = static_cast<int>(m_RectToDraw.width);
		dstRect.h = static_cast<int>(m_RectToDraw.height);

		SDL_Rect srcRect{};
		srcRect.x = static_cast<int>(m_RectToDraw.x);
		srcRect.y = static_cast<int>(m_RectToDraw.y);
		srcRect.w = static_cast<int>(m_RectToDraw.width);
		srcRect.h = static_cast<int>(m_RectToDraw.height);

		dae::Renderer::GetInstance().RenderTexture(*m_AnimationSprite, dstRect, srcRect, isFlip);
	}


	glm::vec2 Animation::GetCurrentDimensions()
	{
		glm::vec2 totalDim = m_AnimationSprite->GetDimensions();
		totalDim.x /= m_Cols;
		totalDim.y /= m_Rows;

		return totalDim;
	}

	bool Animation::IsInFinalFrame() const
	{
		return (m_CurrentFrame == (m_TotalFrames - 1));
	}

}
