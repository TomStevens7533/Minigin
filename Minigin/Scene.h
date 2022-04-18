#pragma once
#include "SceneManager.h"
#include "SceneColliders.h"
namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update();
		void LateUpdate();

		//start is called after everthing is initialized
		void Start();

		void Render() const;

		inline std::string GetSceneName() { return m_Name; }
		
		ColliderInfo* IsRectColliding(Rectf lookupRect) { return m_SceneGrid.IsRectColliding(lookupRect); };
		ColliderInfo* IsPointInCollider(glm::vec2 point) { return m_SceneGrid.IsPointInCollider(point); };

		ColliderInfo* IsRectColliding(Rectf lookupRect, std::string tag) { return m_SceneGrid.IsRectColliding(lookupRect, tag); };
		ColliderInfo* IsPointInCollider(glm::vec2 point, std::string tag) { return m_SceneGrid.IsPointInCollider(point, tag); };

		void AddColliderToScene(ColliderInfo colInfo) { m_SceneGrid.AddCollider(colInfo); };

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};
		SceneColliders m_SceneGrid;
		static unsigned int m_IdCounter; 
	};

}
