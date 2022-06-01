#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
#include "Subject.h"
#include "structs.h"
namespace dae {

	enum class BoxColliderType {
		STATIC, DYNAMIC
	};

	class BoxColliderComponent : public BaseComponent
	{
	public:
		BoxColliderComponent(std::string tag, int precision = 0);
		~BoxColliderComponent();

		void Render() const override;
		void Update() override;
		void LateUpdate() override {};
		virtual void Start() override;

		void DisableCollider();
		void EnableCollider();

		void AddListener(ColliderCallbacks otherComp);
		void RemoveListender(ColliderCallbacks otherComp);

		void SetNewType(BoxColliderType type);
		void SetNewWidth(float size);
		void SetNewHeight(float size);
		void SetNewPos(glm::vec2 pos);

		inline glm::vec2 GetDimension() const { return m_Dimensions; };
		const dae::ColliderInfo& GetColliderInfo() const;

		void OnOverlapStay(const std::shared_ptr<ColliderInfo> otherCollider);
		void OnOverlapEnter(const std::shared_ptr<ColliderInfo> otherCollider);
		void OnOverlaExit(const std::shared_ptr<ColliderInfo> otherCollider);



		BoxColliderComponent(const BoxColliderComponent& other) = delete;
		BoxColliderComponent(BoxColliderComponent&& other) = delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) = delete;


	private:
		glm::vec2 m_Dimensions;
		std::string m_ColliderTag;
		int m_Precision{};
		BoxColliderType m_ColType = BoxColliderType::DYNAMIC;
		std::shared_ptr<ColliderInfo> m_pColliderInfo{nullptr};
		std::vector<ColliderCallbacks>m_RegisteredListeners;
	};
}
