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

	ImGui::Begin("RIP", nullptr, window_flags);
	ImGui::SetWindowSize({ 300, 160 });

	ImGui::Text("Boeken toe!!!");
	ImGui::Text("You lost oh no ca nest pas bien hייי please trya again a");
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

