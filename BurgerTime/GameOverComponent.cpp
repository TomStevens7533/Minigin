#include "GameOverComponent.h"
#include "../Imgui/imgui.h"
#include "BurgerTimeManager.h"
#include <string>

void Burger::GameoverComp::Render() const
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::SetNextWindowPos({ 180,160 });
	ImGui::Begin("RIP", nullptr, window_flags);
	ImGui::SetWindowSize({ 300, 160 });
	ImGui::Spacing();
	ImGui::Text("Boeken toe!!!");
	ImGui::Spacing();
	ImGui::Text("You lost oh no ca nest pas bien please trya again a");
	ImGui::Spacing();
	ImGui::Indent();

	std::string score = "Score :";
	score += std::to_string(GameManager::GetInstance().GetScore());
	ImGui::Text(score.c_str());
	ImGui::Unindent();
	
	
	if (ImGui::Button("GO TO MAIN MENU!")) {
		GameManager::GetInstance().GoToNextLevel();
	}
	ImGui::End();
}

void Burger::GameoverComp::Start()
{
	GameManager::GetInstance().ResetScore();
}

