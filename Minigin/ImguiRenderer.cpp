#include "MiniginPCH.h"
#include "ImguiRenderer.h"

#include "Renderer.h"
#include "SDL_opengl.h"
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"
#include "SDL_video.h"

void dae::ImguiRenderer::Init(SDL_Window* win)
{
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(win, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::ImguiRenderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void dae::ImguiRenderer::Render() const
{

	//ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void dae::ImguiRenderer::NewFrame(SDL_Window* win)
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(win);
	ImGui::NewFrame();
}

