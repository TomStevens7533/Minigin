#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "EntityManager.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:

		void Start();
		void Update();
		void LateUpdate();
		void Render() const;

		template<class TComponent>
		bool AddComponent(std::shared_ptr<BaseComponent> component) {
			component->SetAttachedGo(this);
			return m_EntityManager.AddComponent<TComponent>(component);
		}
		template<class TComponent>
		TComponent* AddOrGetComponent() {
			return m_EntityManager.AddOrGetComponent<TComponent>(this).get();
		}
		template<class TComponent>
		TComponent* const GetComponent() {
			return m_EntityManager.GetComponent<TComponent>().get();
		}
		template<class TComponent>
		void RemoveComponent() {
			return m_EntityManager.RemoveComponent<TComponent>();
		}
		void SetPosition(float x, float y);
		void SetPosition(glm::vec2 pos);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void SetParent(GameObject* parent);
		GameObject* GetParent() const;
		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(int Index) const;
		void RemoveChild(int index);
		void RemoveChild(std::shared_ptr<GameObject> childToRemove);
		void AddChild(std::shared_ptr<GameObject>& go);
		void ChangeRootPos(int newRootPos);
		int GetPosFromRoot();

		inline Transform& GetTransform() { return m_Transform; }
		glm::vec3 RelativePositionToParent();

		//functionality
		void SetScene(Scene* currsScene) { m_CurrentScene = currsScene; };
		Scene* GetScene() { return m_CurrentScene; };

		bool GetDestroyFlag() { return m_DestoryFlag; }
		void SetDestroyFlag(bool isDestroy) { m_DestoryFlag = isDestroy; }
		bool GetInitState() { return m_IsInitialized; }

	private:
		Transform m_Transform;
		// todo: mmm, every gameobject has a texture? Is that correct?

		//parent child
		GameObject* m_Parent = nullptr;
		std::vector<std::shared_ptr<GameObject>> m_Children;
		int m_PositionFromRoot = 0;
		//Entities
		EntityManager m_EntityManager;

		bool m_DestoryFlag = false;
		bool m_IsInitialized = false;
		std::string name{};
		Scene* m_CurrentScene = nullptr;

		
	};
}
