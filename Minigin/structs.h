#pragma once
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
	};

}
