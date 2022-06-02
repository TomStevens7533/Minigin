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

	
	struct ColliderInfo;
	struct ColliderCallbacks
	{
		std::function<void(const std::shared_ptr<ColliderInfo>)> OverlapStayFunc = nullptr;
		std::function<void(const std::shared_ptr<ColliderInfo>)> OverlapEnterFunc = nullptr;
		std::function<void(const std::shared_ptr<ColliderInfo>)> OverlopExitFunc = nullptr;
	};

	struct ColliderInfo
	{
		ColliderInfo() = default;
		ColliderInfo(ColliderCallbacks& callback) : m_ColliderCallback{callback} {};
		Rectf m_ColliderRect{};
		std::string tag = "None";
		GameObject* m_pAttachedGameObject = nullptr;
		bool IsEnabled = true;
		std::vector<std::weak_ptr<ColliderInfo>> m_OverlappingColliders;
	private:
		friend class SceneColliders;
		ColliderCallbacks m_ColliderCallback;		
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
