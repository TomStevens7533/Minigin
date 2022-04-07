#pragma once
#include <limits.h>
namespace dae {
	class GameObject;
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void Render() const = 0;

		GameObject* GetAttachedGameObject() const { return m_pParent; }
		void SetAttachedGo(GameObject* parentGO) { m_pParent = parentGO; }
	protected:
		GameObject* m_pParent = nullptr;
	};


}
