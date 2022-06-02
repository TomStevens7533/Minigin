#pragma once
#include "Singleton.h"
#include "ImguiRenderer.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	struct WindowInformation
	{
		int width{};
		int height{};
	};

	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_clearColor{};
		ImguiRenderer m_ImguiRender;
		WindowInformation m_WindowInfo;
	public:
		void Init(int width, int height);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect dstRect, const SDL_Rect srcRect, bool isFlipped = false) const;
		void DrawPoint(float x, float y);
		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
		WindowInformation GetInfo() { return m_WindowInfo; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

