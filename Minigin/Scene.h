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
		void Add(const std::shared_ptr<GameObject>& object);

		void Update();
		void FixedUpdate();

		//start is called after everthing is initialized
		void Start();

		void Render() const;

		inline std::string GetSceneName() { return m_Name; }
		
		//Collision

		std::shared_ptr<ColliderInfo> AddColliderToScene(ColliderInfo colInfo) { return m_SceneGrid.AddCollider(colInfo); };
		bool RemoveCollider(std::shared_ptr<ColliderInfo> colInfo); 

		//Raycasts
		std::shared_ptr<ColliderInfo> SceneRaycast(glm::vec2 pos, glm::vec2 dir, float length, std::string tag, int steps = 10, const std::shared_ptr<ColliderInfo> colliderToIgnore = std::make_shared<ColliderInfo>());
		std::shared_ptr<ColliderInfo> SceneRectcast(Rectf pos, glm::vec2 dir, float length, std::string tag, int steps = 10, const std::shared_ptr<ColliderInfo> colliderToIgnore = std::make_shared<ColliderInfo>());

		const std::vector<GameObject*> GetGameObjectsWithTag(std::string lookupName);
		inline void SetDestoryFlag() { m_DestroyNeeded = true; }
		inline bool GetDestroyFlag() const { return m_DestroyNeeded; }


		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	private:
		void DestroySceneObject(std::shared_ptr<GameObject> go);
	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		SceneColliders m_SceneGrid;
		bool m_IsStarted = false;
		bool m_DestroyNeeded = false;
	};

}
