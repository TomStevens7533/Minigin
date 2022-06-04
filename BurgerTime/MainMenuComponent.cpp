#include "MainMenuComponent.h"
#include "../Imgui/imgui.h"
#include "BurgerTimeManager.h"
#include "ServiceLocator.h"

void Burger::MainMenuComp::Start()
{
	

}

void Burger::MainMenuComp::Render() const
{

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::Begin("BURGER TIME!!!!!!!!!!!!!!", nullptr, window_flags);
	ImGui::SetWindowSize({ 300, 160 });

	ImGui::Text("Welcome to epic Burger time");
	ImGui::Spacing();
	const char* items[] = { "COOP", "PVP", "SOLO"};
	Gamemode selectedGamemode = Gamemode::SOLO;
	if (ImGui::Combo(" :Mode", (int*)&selectedGamemode, items, IM_ARRAYSIZE(items))) {
		GameManager::GetInstance().SetGamemode(selectedGamemode);
	}
	ImGui::Spacing();
	if (ImGui::Button("PLAY!")) {
		GameManager::GetInstance().GoToNextLevel();

		ServiceLocator::GetSoundSystem().StopAll();
	}
	ImGui::End();
}

