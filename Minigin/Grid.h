#pragma once
#include <array>
class Grid
{
public:
	Grid();
	~Grid();
	void SetTerrain(glm::vec2 pos, glm::vec2 size);
	bool IsHittingTerrain(glm::vec2 pos, glm::vec2 velocity);

private:
	std::array<std::array<bool, 480>, 640>  m_GridCells{};
};
