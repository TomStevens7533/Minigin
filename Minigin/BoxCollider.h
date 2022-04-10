#pragma once
#include "Subject.h"
#include "BaseComponent.h"
#include <glm/glm.hpp>
namespace dae {
	class BoxColliderComponent : public BaseComponent, public Subject
	{
	public:
		BoxColliderComponent( );
		BoxColliderComponent(int width, int height);
		void Render() const override {};
		void Update() override {};
		void LateUpdate() override;
		virtual void Start() override {};

	private:
		glm::vec2 m_Dimensions;
	};


}
