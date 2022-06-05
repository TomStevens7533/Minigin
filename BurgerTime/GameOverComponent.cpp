#include "GameOverComponent.h"
#include "../Imgui/imgui.h"
#include "BurgerTimeManager.h"
#include <string>
#include "Renderer.h"


void Burger::GameoverComp::Start()
{
	GameManager::GetInstance().ResetScore();
	m_HighScoreVec = GameManager::GetInstance().ReadScore();
}

void Burger::GameoverComp::Render() const
{
	dae::WindowInformation windowInfo = dae::Renderer::GetInstance().GetInfo();
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::SetNextWindowPos({ windowInfo.width / 4.f,windowInfo.height / 4.f });
	ImGui::Begin("RIP", nullptr, window_flags);
	ImGui::SetWindowSize({ windowInfo.width / 2.f, windowInfo.height / 2.f });
	ImGui::Spacing();
	ImGui::Text("Boeken toe!!!");
	ImGui::Spacing();
	ImGui::Text("You lost oh no ca nest pas bien please trya again a");
	ImGui::Spacing();
	
	
	if (ImGui::Button("GO TO MAIN MENU!")) {
		GameManager::GetInstance().GoToNextLevel();
	}

	ImGui::Spacing();
	int selectedIndex = 0;
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
	ImGui::Unindent();

	ImGui::End();
}


