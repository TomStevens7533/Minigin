#pragma once
#include "BaseComponent.h"
#include <memory>
#include <string>
#include <map>
#include "Animation.h"

namespace dae {
	class Texture2D;
	class SpriteComponent final : public BaseComponent
	{
	public:
		//SpriteComponent(int startCol, int startRow, int col, int row, std::shared_ptr<Texture2D> fullTexture);
		SpriteComponent(std::string path, int collAmount, int rowAmount, float timeFrame);
		~SpriteComponent();

		bool AddAnimation(const std::string key,int starCol, int startRow, int endCol, int endRow);
		void SetActiveAnimation(std::string key);
		void SetFlipState(bool isFlip = true) { m_IsFlipped = isFlip; };
		glm::vec2 GetCurrentAnimDimensions();

		void Render() const override;
		void Update() override;
		void LateUpdate() override {};
		virtual void Start() override {};


		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent(SpriteComponent&&) = delete;
		SpriteComponent& operator= (const SpriteComponent&) = delete;
		SpriteComponent& operator= (const SpriteComponent&&) = delete;

	private:
		std::map<std::string, Animation> m_AnimationMap;
		Animation* m_ActiveAnimation = nullptr;
		std::shared_ptr<Texture2D> m_SpriteTexture;
	private:
		int m_widthPerCell{};
		int m_HeightPerCell{};
		float m_TimeFrame{};
		bool m_IsFlipped{false};
		int m_TotalCol{0};
		int m_TotalRow{ 0 };

	};

}

