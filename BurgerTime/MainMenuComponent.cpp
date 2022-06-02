#include "MainMenuComponent.h"
#include "../Imgui/imgui.h"
#include "BurgerTimeManager.h"

void Burger::MainMenuComp::Render() const
{

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::Begin("BURGER TIME!!!!!!!!!!!!!!", nullptr, window_flags);
	ImGui::SetWindowSize({ 300, 160 });

	ImGui::Text("Welcome to epic Burger time");
	const char* items[] = { "PVP", "PVE", "COOP"};
	Gamemode selectedGamemode{};
	if (ImGui::Combo(" :Mode", (int*)&selectedGamemode, items, IM_ARRAYSIZE(items))) {
		GameManager::GetInstance().SetGamemode(selectedGamemode);
	}
	if (ImGui::Button("PLAY!")) {
		GameManager::GetInstance().GoToNextLevel();
	}
	ImGui::End();
}

 