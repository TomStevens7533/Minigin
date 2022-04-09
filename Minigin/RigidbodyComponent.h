#pragma once
#include "Subject.h"
#include "BaseComponent.h"
#include <glm/glm.hpp>
namespace dae {
	class RigidbodyComponent : public BaseComponent, public Subject
	{
	public:
		void Render() const override {};
		void Update() override {};
		void LateUpdate() override;
		virtual void Start() override {};

		void AddVelocity(float x, float y);
		void SetVelocity(float x, float y);
		void SetVelocityX(float x);
		void SetVelocityY(float y);


	private:
		glm::vec2 m_Velocity;
	};


}
