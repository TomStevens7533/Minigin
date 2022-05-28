#pragma once
#include <functional>
namespace dae {
	struct Rectf
	{
		float x;
		float y;
		float width;
		float height;

		inline bool operator==(const Rectf& rhs);
	};
	class GameObject;

	

	struct ColliderInfo
	{
		Rectf m_ColliderRect;
		std::string tag = "None";
		GameObject* m_pAttachedGameObject = nullptr;
		bool IsEnabled = true;
		std::vector<std::weak_ptr<ColliderInfo>> m_OverlappingColliders;


		std::function<void(const std::shared_ptr<ColliderInfo>)> OverlapStayFunc = nullptr;
		std::function<void(const std::shared_ptr<ColliderInfo>)> OverlapEnterFunc = nullptr;
		std::function<void(const std::shared_ptr<ColliderInfo>)> OverlopExitFunc = nullptr;


		
	};
	struct ColliderCallbacks
	{
		std::function<void(const std::shared_ptr<ColliderInfo>)> OverlapStayFunc = nullptr;
		std::function<void(const std::shared_ptr<ColliderInfo>)> OverlapEnterFunc = nullptr;
		std::function<void(const std::shared_ptr<ColliderInfo>)> OverlopExitFunc = nullptr;
	};

	enum class HorizontalDirection {
		NONE,
		LEFT,
		RIGHT
	};
	enum class VerticalDirection {
		NONE,
		UP,
		DOWN
	};

}
