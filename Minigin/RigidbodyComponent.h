#pragma once
#include "Subject.h"
#include "BaseComponent.h"
namespace dae {
	class RigidbodyComponent : public BaseComponent, public Subject
	{
	public:
		void Render() const override {};
		void Update() override {};
		void LateUpdate() override {};
		virtual void Start() override {};

	};


}
