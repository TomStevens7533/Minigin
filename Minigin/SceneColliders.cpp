#include "MiniginPCH.h"
#include "SceneColliders.h"
#include "Renderer.h"


using namespace dae;
std::shared_ptr<ColliderInfo> SceneColliders::AddCollider(ColliderInfo info)
{
	m_SceneColliderVec.push_back(std::make_shared<ColliderInfo>(info));
	return m_SceneColliderVec.back();
}

void SceneColliders::RemoveCollider(std::string tag, bool deleteAll /*= false*/)
{
	if (deleteAll == true) {
		m_SceneColliderVec.erase(std::remove_if(m_SceneColliderVec.begin(), m_SceneColliderVec.end(), [&tag](std::shared_ptr<ColliderInfo> currInfo) {
			return (currInfo->tag == tag);
		})
		, m_SceneColliderVec.end());
	}
	else {
		auto it = std::remove_if(m_SceneColliderVec.begin(), m_SceneColliderVec.end(), [&tag](std::shared_ptr<ColliderInfo> currInfo) {
			return (currInfo->tag == tag);
			});
		m_SceneColliderVec.erase(it);
	}

}

std::shared_ptr<ColliderInfo> SceneColliders::IsRectColliding(Rectf lookupRect)
{
	for (size_t i = 0; i < m_SceneColliderVec.size(); i++)
	{
		if (AreRectsOverlapping(lookupRect, m_SceneColliderVec[i]->m_ColliderRect)) {
			return m_SceneColliderVec[i];
		}
	}
	return nullptr;
}

std::shared_ptr<ColliderInfo> SceneColliders::IsRectColliding(Rectf lookupRect, std::string tag)
{
	for (size_t i = 0; i < m_SceneColliderVec.size(); i++)
	{
		if (!(lookupRect == m_SceneColliderVec[i]->m_ColliderRect)) {
			if (m_SceneColliderVec[i]->tag == tag && AreRectsOverlapping(lookupRect, m_SceneColliderVec[i]->m_ColliderRect)) {
				return m_SceneColliderVec[i];
			}
		}
		
	}
	return nullptr;
}

std::shared_ptr<ColliderInfo> SceneColliders::IsPointInCollider(glm::vec2 point)
{
	for (size_t i = 0; i < m_SceneColliderVec.size(); i++)
	{
		if (IsPointInRect(m_SceneColliderVec[i]->m_ColliderRect, point)) {
			return m_SceneColliderVec[i];
		}
	}
	return nullptr;
}

std::shared_ptr<ColliderInfo> SceneColliders::IsPointInCollider(glm::vec2 point, std::string tag)
{
	for (size_t i = 0; i < m_SceneColliderVec.size(); i++)
	{
		if (m_SceneColliderVec[i]->tag == tag && IsPointInRect(m_SceneColliderVec[i]->m_ColliderRect, point)) {
			return m_SceneColliderVec[i];
		}
	}
	return nullptr;
}

std::shared_ptr<dae::ColliderInfo> SceneColliders::IsPointInCollider(glm::vec2 point, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag)
{
	for (size_t i = 0; i < m_SceneColliderVec.size(); i++)
	{
		if (colliderToIgnore != m_SceneColliderVec[i]  && IsPointInRect(m_SceneColliderVec[i]->m_ColliderRect, point)) {
			if(tag == m_SceneColliderVec[i]->tag)
				return m_SceneColliderVec[i];
		}
	}
	return nullptr;
}

bool SceneColliders::AreRectsOverlapping(Rectf lhs, Rectf rhs)
{

	// If one rectangle is on left side of the other
	if ((lhs.x + lhs.width) < rhs.x || (rhs.x + rhs.width) < lhs.x)
	{
		return false;
	}

	// If one rectangle is under the other
	if (lhs.y > (rhs.y + rhs.height) || rhs.y > (lhs.y + lhs.height))
	{
		return false;
	}

	return true;
}

bool SceneColliders::IsPointInRect(Rectf lhs, glm::vec2 point)
{
	if (point.x >= lhs.x && point.x <= (lhs.x + lhs.width) && point.y >= lhs.y && point.y <= (lhs.y + lhs.height))
		return true;

	return false;
}

std::shared_ptr<dae::ColliderInfo> SceneColliders::SceneRaycast(glm::vec2 pos, glm::vec2 dir,
	float length, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag, int steps)
{
	assert(steps > 0);
	float stepPercentage = (length / steps);
	for (size_t i = 0; i < steps; i++)
	{
		glm::vec2 newPos = pos + glm::vec2(dir.x * ((stepPercentage) * i), dir.y * ((stepPercentage) * i));
		auto collInfo = IsPointInCollider(newPos, colliderToIgnore, tag);

		if (collInfo)
			return collInfo;

	}
	return nullptr;

}

































//#include "Grid.h"
//SceneColliders::SceneColliders()
//{
//	for (auto& arr : m_GridCells)
//		std::fill(std::begin(arr), std::end(arr), false);
//}
//
//SceneColliders::~SceneColliders()
//{
//	
//}
//
//void SceneColliders::SetTerrain(glm::vec2 pos, glm::vec2 size)
//{
//	
//
//	if (((pos.x + size.x) < 640 && (pos.y + size.y) < 480) && (pos.x + size.x) > 0 && (pos.y + size.y) > 0) {
//		//Is in grid
//		for (size_t x = static_cast<int>(std::round(pos.x)); x < static_cast<int>(std::round(pos.x + size.x)); x++)
//		{
//			for (size_t y = static_cast<int>(std::round(pos.y - size.y)); y < static_cast<int>(std::round(pos.y)); y++)
//			{
//				if (x > 0 && x < 640 && y > 0 && y < 480)
//					m_GridCells[x][y] = true;
//			}
//		}
//	}
//}
//
//bool SceneColliders::IsHittingTerrain(glm::vec2 pos, glm::vec2 velocity)
//{
//	glm::vec2 futurePos = pos + velocity;
//	int xId = static_cast<int>(std::round(futurePos.x));
//	int yId = static_cast<int>(std::round(futurePos.y));
//
//	if(xId > 0 && xId < 640 && yId > 0 && yId < 480)
//		if (m_GridCells[xId][yId])
//			return true;
//
//	return false;
//}
//


