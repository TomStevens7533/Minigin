#pragma once
#include <vector>
#include <iostream>
#include "structs.h"
#include "glm/mat4x4.hpp"
namespace dae {
	class GameObject;

	class SceneColliders final
	{
	public:
		SceneColliders() = default;
		~SceneColliders() = default;
		std::shared_ptr<ColliderInfo> AddCollider(ColliderInfo info);
		//bool RemoveCollider(std::string tag, bool deleteAll = false);
		bool RemoveCollider(const std::shared_ptr<ColliderInfo> col);

		void UpdateColliders();


		const std::vector <const dae::ColliderInfo* > GetAllCollidersWithTag(std::string tag) const;
		
		const std::shared_ptr<ColliderInfo> RectCast(Rectf pos, glm::vec2 dir, float length, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag, int steps = 10);
		const std::shared_ptr<ColliderInfo> SceneRaycast(glm::vec2 pos, glm::vec2 dir, float length, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag, int steps = 10);
	public:
		SceneColliders(const SceneColliders& other) = delete;
		SceneColliders(SceneColliders&& other) = delete;
		SceneColliders& operator=(const SceneColliders& other) = delete;
		SceneColliders& operator=(SceneColliders&& other) = delete;
	private:
		std::shared_ptr<ColliderInfo> IsRectCollidingScene(Rectf lookupRect, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag);
		std::shared_ptr<ColliderInfo> IsRectCollidingScene(Rectf lookupRect);

		std::shared_ptr<ColliderInfo> IsPointInColliderScene(glm::vec2 point);
		std::shared_ptr<ColliderInfo> IsPointInColliderScene(glm::vec2 point, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag);
	private:
		std::vector<std::shared_ptr<ColliderInfo>> m_SceneColliderVec;
	};

}
