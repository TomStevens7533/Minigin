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
		std::shared_ptr<ColliderInfo> AddCollider(ColliderInfo info);
		void RemoveCollider(std::string tag, bool deleteAll = false);
		std::shared_ptr<ColliderInfo> IsRectColliding(Rectf lookupRect);
		std::shared_ptr<ColliderInfo> IsPointInCollider(glm::vec2 point);

		std::shared_ptr<ColliderInfo> IsRectColliding(Rectf lookupRect, std::string tag);
		std::shared_ptr<ColliderInfo> IsPointInCollider(glm::vec2 point, std::string tag);
	public:
		SceneColliders(const SceneColliders& other) = delete;
		SceneColliders(SceneColliders&& other) = delete;
		SceneColliders& operator=(const SceneColliders& other) = delete;
		SceneColliders& operator=(SceneColliders&& other) = delete;
	private:
		bool AreRectsOverlapping(Rectf lhs, Rectf rhs);
		bool IsPointInRect(Rectf lhs, glm::vec2 point);
	private:
		std::vector<std::shared_ptr<ColliderInfo>> m_SceneColliderVec;
	};

}
