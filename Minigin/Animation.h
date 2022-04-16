#pragma once
#include <memory>
#include "Transform.h"
#include "structs.h"
struct SDL_Texture;
namespace dae {
	class Texture2D;
	class Animation
	{
	public:
		Animation(SDL_Texture* animTexture, int widthPerCell, int heightPerCell, float m_TimeFrame);
		Animation(const Animation& lhs);

		~Animation();

		void Update();
		void Render(Transform tr, bool isFlip) const;

	private:
		std::shared_ptr<Texture2D> m_AnimationSprite;
		Rectf m_RectToDraw;
	private:
		float m_FrameTime = 0.2f;
		int m_CurrentFrame{ 0 };

		int m_Cols{};
		int m_Rows{};

		int m_TotalFrames{};
		float m_AccumulatedTime{ 0.f };
		bool m_Backwards = false;

		bool m_IsPauzed = false;

	};


}
