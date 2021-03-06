#include "MiniginPCH.h"
#include "SceneColliders.h"
#include "Renderer.h"
#include <algorithm>
#include "MathHelper.h"

using namespace dae;
std::shared_ptr<ColliderInfo> SceneColliders::AddCollider(ColliderInfo info)
{
	auto newColl = std::make_shared<ColliderInfo>(info);
	m_SceneColliderVec.push_back(newColl);
	return newColl;
}

bool SceneColliders::RemoveCollider(const std::shared_ptr<ColliderInfo> col)
{
	if (m_SceneColliderVec.size() > 0) {
		if (m_SceneColliderVec.erase(std::remove(m_SceneColliderVec.begin(), m_SceneColliderVec.end(), col), m_SceneColliderVec.end()) != m_SceneColliderVec.end()) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

std::shared_ptr<ColliderInfo> SceneColliders::IsRectCollidingScene(Rectf lookupRect)
{
	for (size_t i = 0; i < m_SceneColliderVec.size(); i++)
	{
		if (MathHelper::AreRectsOverlapping(lookupRect, m_SceneColliderVec[i]->m_ColliderRect)) {
			return m_SceneColliderVec[i];
		}
	}
	return nullptr;
}

std::shared_ptr<dae::ColliderInfo> SceneColliders::IsRectCollidingScene(Rectf lookupRect, const std::shared_ptr<ColliderInfo>, std::string tag)
{
	for (size_t i = 0; i < m_SceneColliderVec.size(); i++)
	{
		if (MathHelper::AreRectsOverlapping(m_SceneColliderVec[i]->m_ColliderRect, lookupRect)) {
			if (tag == m_SceneColliderVec[i]->tag)
				return m_SceneColliderVec[i];
		}
	}
	return nullptr;
}

std::shared_ptr<ColliderInfo> SceneColliders::IsPointInColliderScene(glm::vec2 point)
{
	for (size_t i = 0; i < m_SceneColliderVec.size(); i++)
	{
		if (MathHelper::IsPointInRect(m_SceneColliderVec[i]->m_ColliderRect, point)) {
			return m_SceneColliderVec[i];
		}
	}
	return nullptr;
}


std::shared_ptr<dae::ColliderInfo> SceneColliders::IsPointInColliderScene(glm::vec2 point, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag)
{
	for (size_t i = 0; i < m_SceneColliderVec.size(); i++)
	{
		if (colliderToIgnore != m_SceneColliderVec[i] && MathHelper::IsPointInRect(m_SceneColliderVec[i]->m_ColliderRect, point)) {
			if (tag == m_SceneColliderVec[i]->tag)
				return m_SceneColliderVec[i];
		}
	}
	return nullptr;
}


const std::vector <const dae::ColliderInfo* > SceneColliders::GetAllCollidersWithTag(std::string tag) const
{
	std::vector<const dae::ColliderInfo*> m_FilterVec;
	for (size_t i = 0; i < m_SceneColliderVec.size(); i++)
	{
		if (m_SceneColliderVec[i]->tag == tag) {
			//is of right tag
			m_FilterVec.push_back(m_SceneColliderVec[i].get());
		}

	}
	return m_FilterVec;
}

void SceneColliders::UpdateColliders()
{
	for(auto& lookUpElement : m_SceneColliderVec) {

		for (auto& CompareElement : m_SceneColliderVec)
		{
			if (lookUpElement != CompareElement) {

				if (CompareElement->IsEnabled == false)
					continue;

				bool isOverlapping = MathHelper::AreRectsOverlapping(lookUpElement->m_ColliderRect, CompareElement->m_ColliderRect);

				auto it = std::find_if(lookUpElement->m_OverlappingColliders.begin()
					, lookUpElement->m_OverlappingColliders.end(), [&CompareElement](auto weaklement) {
						return weaklement.lock() == CompareElement;
					
					});
				if (it != lookUpElement->m_OverlappingColliders.end()) {
					if (!isOverlapping) {
						//Call exit
						lookUpElement->m_ColliderCallback.OverlopExitFunc(CompareElement);
						lookUpElement->m_OverlappingColliders.erase(it);
						continue;

					}
					//Call overlapp
					lookUpElement->m_ColliderCallback.OverlapStayFunc(CompareElement);
					continue;

				}
				//Cal overlap functions
				else {
					if (isOverlapping) {
						//EnterOverlap;
						lookUpElement->m_ColliderCallback.OverlapEnterFunc(CompareElement);
						lookUpElement->m_OverlappingColliders.push_back(CompareElement);
					}
				}
				
			}
		}
	}
}

const std::shared_ptr<dae::ColliderInfo> SceneColliders::SceneRaycast(glm::vec2 pos, glm::vec2 dir, float length, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag, int steps /*= 10*/)
{
	assert(steps > 0);
	float stepPercentage = (length / steps);
	for (int i = 1; i <= (steps); i++)
	{
		float currStepAmount = ((stepPercentage)*static_cast<float>(i));
		glm::vec2 steppedDir = glm::vec2{ dir.x * currStepAmount, dir.y * currStepAmount };
		glm::vec2 newPos = pos + steppedDir;
		auto collInfo = IsPointInColliderScene(newPos, colliderToIgnore, tag);

		if (collInfo)
			return collInfo;

	}
	return nullptr;
}

const std::shared_ptr<dae::ColliderInfo> SceneColliders::RectCast(Rectf pos, glm::vec2 dir, float length, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag, int steps /*= 10*/)
{
	assert(steps > 0);
	float stepPercentage = (length / steps);
	for (int i = 1; i <= (steps); i++)
	{
		Rectf lookupRect = pos;
		float currStepAmount = ((stepPercentage) * static_cast<float>(i));

		glm::vec2 steppedDir = glm::vec2{ dir.x * currStepAmount, dir.y * currStepAmount };
		lookupRect.x += steppedDir.x;
		lookupRect.y += steppedDir.y;


		auto collInfo = IsRectCollidingScene(lookupRect, colliderToIgnore, tag);
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


