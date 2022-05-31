#pragma once
namespace dae
{
	class Scene;
	class SceneObject
	{
	public:
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void Render() const = 0;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

		void SetScene(Scene* currsScene) { m_CurrentScene = currsScene; };
		Scene* GetScene() { return m_CurrentScene; };

		bool GetDestroyFlag() { return m_DestoryFlag; }
		void SetDestroyFlag(bool isDestroy) { m_DestoryFlag = isDestroy; }
		bool GetInitState() { return m_IsInitialized; }

	protected:
		bool m_DestoryFlag = false;
		bool m_IsInitialized = false;
	private:
		Scene* m_CurrentScene = nullptr;

	};
}
