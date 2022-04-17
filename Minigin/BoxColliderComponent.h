#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
namespace dae {
	class BoxColliderComponent : public BaseComponent
	{
	public:
		BoxColliderComponent(int width, int height);
		BoxColliderComponent(glm::vec2 dimensions);

		void Render() const override {};
		void Update() override {};
		void LateUpdate() override;
		virtual void Start() override;


		BoxColliderComponent(const BoxColliderComponent& other) = delete;
		BoxColliderComponent(BoxColliderComponent&& other) = delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) = delete;


	private:
		glm::vec2 m_Dimensions;
	};
}
