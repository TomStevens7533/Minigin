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
		std::function<void(const std::shared_ptr<ColliderInfo>)> m_OverlapFunc;
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
