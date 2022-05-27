#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
#include "Subject.h"
#include "structs.h"
namespace dae {

	struct CollisionArgs : public EventArgs {
		ColliderInfo info;
	};

	class BoxColliderComponent : public BaseComponent, public Subject
	{
	public:
		BoxColliderComponent(int width, int height, std::string tag, int precision = 0);
		BoxColliderComponent(glm::vec2 dimensions, std::string tag, int precision = 0);
		BoxColliderComponent(std::string tag, int precision = 0);
		~BoxColliderComponent();

		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		virtual void Start() override;

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
		std::shared_ptr<ColliderInfo> m_pColliderInfo{nullptr};
	};
}
