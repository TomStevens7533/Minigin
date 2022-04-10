#pragma once
#include "BaseComponent.h"
#include "Subject.h"
namespace dae {
	class PetterPepperComponent : public BaseComponent, public Subject
	{
	public:
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() const override;
	protected:

	private:
	};

}

