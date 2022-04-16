#pragma once
class Grid
{
public:
	Grid();
	~Grid();
	void SetTerrain(glm::vec2 pos, glm::vec2 size);
	bool IsHittingTerrain(glm::vec2 pos, glm::vec2 velocity);

private:
	bool m_GridCells[640][480]{false};
};
