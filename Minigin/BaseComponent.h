#pragma once
#include <limits.h>
namespace dae {
	class GameObject;
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;

		virtual void Render() const = 0;

		GameObject* GetAttachedGameObject() const { return m_Parent; }
		void SetAttachedGo(GameObject* parentGO) { m_Parent = parentGO; }
	private:
		GameObject* m_Parent = nullptr;
	};


}
