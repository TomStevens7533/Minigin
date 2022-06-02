#pragma once
#include "Singleton.h"

struct SDL_Window;


namespace dae
{
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class ImguiRenderer final
	{
	public:
		void Init(SDL_Window* win);
		void Destroy();
		void Render() const;
		void NewFrame(SDL_Window* win);
	};
}

