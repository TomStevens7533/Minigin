#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "EntityManager.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final : public SceneObject
	{
	public:

		void Start() override;
		void Update() override;
		void LateUpdate() override;
		void Render() const override;

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



	private:
		Transform m_Transform;
		// todo: mmm, every gameobject has a texture? Is that correct?

		//parent child
		GameObject* m_Parent = nullptr;
		std::vector<std::shared_ptr<GameObject>> m_Children;
		int m_PositionFromRoot = 0;
		bool m_IsInitialized = false;
		//Entities
		EntityManager m_EntityManager;
		
	};
}
