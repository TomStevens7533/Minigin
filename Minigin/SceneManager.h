#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		std::shared_ptr<dae::Scene> GetScene(const std::string& name);
		void DestroyScene(const std::string& name);



		void Update();
		void FixedUpdate();
		void Render();

		void DestroyFlaggedScenes();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene = nullptr;
	};
}
