#pragma once
#include "BaseComponent.h"
#include <memory>
#include <string>

struct Rectf
{
	float x;
	float y;
	float width;
	float height;
};
namespace dae {
	class Texture2D;
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(int startCol, int startRow, int col, int row, std::shared_ptr<Texture2D> fullTexture);
		SpriteComponent(std::string path,int col, int row);
		~SpriteComponent();

		//void SetFrame(int frame);

		void Render() const override {};
		void Update() override {};
		void LateUpdate() override {};
		virtual void Start() override {};


		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent(SpriteComponent&&) = delete;
		SpriteComponent& operator= (const SpriteComponent&) = delete;
		SpriteComponent& operator= (const SpriteComponent&&) = delete;

	private:
		std::unique_ptr<Texture2D> m_SpriteTexture;
		bool m_IsPauzed = false;
		int m_CurrentFrame = 0;
		int m_MaxFrames = 0;

	};

}

