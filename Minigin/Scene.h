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
		
		//Collision
		std::shared_ptr<ColliderInfo>IsRectColliding(Rectf lookupRect) { return m_SceneGrid.IsRectColliding(lookupRect); };
		std::shared_ptr<ColliderInfo>IsPointInCollider(glm::vec2 point) { return m_SceneGrid.IsPointInCollider(point); };
		std::shared_ptr<ColliderInfo> IsRectColliding(Rectf lookupRect, std::string tag) { return m_SceneGrid.IsRectColliding(lookupRect, tag); };
		std::shared_ptr<ColliderInfo> IsPointInCollider(glm::vec2 point, std::string tag) { return m_SceneGrid.IsPointInCollider(point, tag); };
		std::shared_ptr<ColliderInfo> AddColliderToScene(ColliderInfo colInfo) { return m_SceneGrid.AddCollider(colInfo); };
		//Raycasts
		std::shared_ptr<ColliderInfo> SceneRaycast(glm::vec2 pos, glm::vec2 dir, float length, const std::shared_ptr<ColliderInfo> colliderToIgnore, std::string tag);


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
