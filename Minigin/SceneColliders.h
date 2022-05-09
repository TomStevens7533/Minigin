#pragma once
#include <vector>
#include <iostream>
#include "structs.h"
namespace dae {
	class GameObject;
	struct ColliderInfo
	{
		Rectf m_ColliderRect;
		std::string tag = "None";
		GameObject* m_pAttachedGameObject = nullptr;
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
		std::shared_ptr<ColliderInfo> IsPointInCollider(glm::vec2 point, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag);


		std::shared_ptr<ColliderInfo> IsRectColliding(Rectf lookupRect, std::string tag);
		std::shared_ptr<ColliderInfo> IsPointInCollider(glm::vec2 point, std::string tag);

		std::shared_ptr<ColliderInfo> SceneRaycast(glm::vec2 pos, glm::vec2 dir, float length, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag, int steps = 10);

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
