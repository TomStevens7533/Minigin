#include "MiniginPCH.h"
#include "Grid.h"
Grid::Grid()
{
	for (auto& arr : m_GridCells)
		std::fill(std::begin(arr), std::end(arr), false);
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
			for (size_t y = static_cast<int>(std::round(pos.y - size.y)); y < static_cast<int>(std::round(pos.y)); y++)
			{
				if (x > 0 && x < 640 && y > 0 && y < 480)
					m_GridCells[x][y] = true;
			}
		}
	}
}

bool Grid::IsHittingTerrain(glm::vec2 pos, glm::vec2 velocity)
{
	glm::vec2 futurePos = pos + velocity;
	int xId = static_cast<int>(std::round(futurePos.x));
	int yId = static_cast<int>(std::round(futurePos.y));

	if(xId > 0 && xId < 640 && yId > 0 && yId < 480)
		if (m_GridCells[xId][yId])
			return true;

	return false;
}

