#include "MainMenuComponent.h"
#include "../Imgui/imgui.h"
#include "BurgerTimeManager.h"
#include "ServiceLocator.h"
#include <string>
#include "Renderer.h"

void Burger::MainMenuComp::Start()
{

	GameManager::GetInstance().ResetScore();
	m_HighScoreVec = GameManager::GetInstance().ReadScore();
}

bool HighScoreGetter(void* data, int n, const char** out_text)
{
	std::vector<int>* highScoreVec = (std::vector<int>*)data;
	std::string highScore = std::to_string((*highScoreVec)[n]);
	*out_text = highScore.c_str();
	return true;
}

void Burger::MainMenuComp::Render() const
{
	dae::WindowInformation windowInfo = dae::Renderer::GetInstance().GetInfo();
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowPos({ windowInfo.width / 4.f,windowInfo.height / 4.f });
	ImGui::Begin("BURGER TIME!!!!!!!!!!!!!!", nullptr, window_flags);
	ImGui::SetWindowSize({ windowInfo.width / 2.f, windowInfo.height / 2.f });

	ImGui::Text("Welcome to epic Burger time");
	ImGui::Spacing();
	const char* items[] = { "COOP", "PVP", "SOLO" };
	if (ImGui::Combo(" :Mode", (int*)&m_SelectedGamemode, items, IM_ARRAYSIZE(items))) {
		GameManager::GetInstance().SetGamemode(m_SelectedGamemode);
	}
	ImGui::Spacing();
	if (ImGui::Button("PLAY!")) {
		GameManager::GetInstance().GoToNextLevel();
		GameManager::GetInstance().ReadScore();

		ServiceLocator::GetSoundSystem().StopAll();
	}
	ImGui::Spacing();
	size_t selectedIndex = 0;
	//Listbox of hightscore
	ImGui::BeginListBox("HIGHSCORES");
	for (size_t i = 0; i < m_HighScoreVec.size(); i++)
	{
		const bool isSelected = (selectedIndex == i);
		if (ImGui::Selectable(std::to_string(m_HighScoreVec[i]).c_str(), isSelected)) {
			selectedIndex = i;
		}

		// Set the initial focus when opening the combo
		// (scrolling + keyboard navigation focus)
		if (isSelected) {
			ImGui::SetItemDefaultFocus();
		}
	}
	ImGui::EndListBox();



	ImGui::End();
}

