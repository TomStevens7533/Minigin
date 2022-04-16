#include "MiniginPCH.h"
#include "Grid.h"
Grid::Grid()
{
}

Grid::~Grid()
{

}

void Grid::SetTerrain(glm::vec2 pos, glm::vec2 size)
{
	if (((pos.x + size.x) < 640 && (pos.y + size.y) < 480) && (pos.x + size.x) > 0 && (pos.y + size.y) > 0) {
		//Is in grid
		for (size_t x = static_cast<int>(std::round(pos.x)); x < static_cast<int>(std::round(pos.x + size.x)); x++)
		{
			for (size_t y = static_cast<int>(std::round(pos.y)); y < static_cast<int>(std::round(pos.y + size.y)); y++)
			{
				m_GridCells[x][y] = true;
			}
		}
	}
}

bool Grid::IsHittingTerrain(glm::vec2 pos, glm::vec2 velocity)
{
	glm::vec2 futurePos = pos + velocity;
	if (m_GridCells[static_cast<int>(std::round(futurePos.x))][static_cast<int>(std::round(futurePos.y))])
		return true;

	return false;
}

