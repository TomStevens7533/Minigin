#pragma once
#include <vector>
#include <iostream>
#include "structs.h"
namespace dae {
	struct ColliderInfo
	{
		Rectf m_ColliderRect;
		std::string tag = "None";
	};

	class SceneColliders
	{
	public:
		SceneColliders() = default;
		~SceneColliders() = default;
		ColliderInfo * const AddCollider(ColliderInfo info);
		void RemoveCollider(std::string tag, bool deleteAll = false);
		ColliderInfo* IsRectColliding(Rectf lookupRect);
		ColliderInfo* IsPointInCollider(glm::vec2 point);

		ColliderInfo* IsRectColliding(Rectf lookupRect, std::string tag);
		ColliderInfo* IsPointInCollider(glm::vec2 point, std::string tag);
	public:
		SceneColliders(const SceneColliders& other) = delete;
		SceneColliders(SceneColliders&& other) = delete;
		SceneColliders& operator=(const SceneColliders& other) = delete;
		SceneColliders& operator=(SceneColliders&& other) = delete;
	private:
		bool AreRectsOverlapping(Rectf lhs, Rectf rhs);
		bool IsPointInRect(Rectf lhs, glm::vec2 point);
	private:
		std::vector<ColliderInfo> m_SceneColliderVec;
	};

}
