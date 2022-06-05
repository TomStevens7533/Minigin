#pragma once
#include <memory>
#include "Transform.h"
#include "structs.h"
struct SDL_Texture;
namespace dae {
	class Texture2D;
	class Animation final
	{
	public:
		Animation(SDL_Texture* animTexture, int widthPerCell, int heightPerCell, float m_TimeFrame);

		~Animation();

		void Update();
		void Render(Transform tr, bool isFlip) const;
		glm::vec2 GetCurrentDimensions();
		bool IsInFinalFrame() const;


		Animation(const Animation& lhs);
		Animation(Animation&& other) = delete;
		Animation& operator=(const Animation& other) = delete;
		Animation& operator=(Animation&& other) = delete;
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
