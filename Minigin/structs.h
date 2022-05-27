#pragma once
#include <functional>
namespace dae {
	struct Rectf
	{
		float x;
		float y;
		float width;
		float height;

		bool operator==(const Rectf& rhs);
	};
	class GameObject;
	struct ColliderInfo
	{
		Rectf m_ColliderRect;
		std::string tag = "None";
		GameObject* m_pAttachedGameObject = nullptr;
		std::function<void(const std::shared_ptr<ColliderInfo>)> m_OverlapStayFunc;
		std::function<void(const std::shared_ptr<ColliderInfo>)> m_OverlapEnterFunc;
		std::function<void(const std::shared_ptr<ColliderInfo>)> m_OverlapExitFunc;

		//Const nest pas possible? c++ no good
		std::vector<std::weak_ptr<ColliderInfo>> m_OverlappingColliders;
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
