#pragma once
#include "BaseComponent.h"
#include <memory>
#include "EventType.h"
namespace dae {
	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void onNotify(const BaseComponent* entity, EventType event) = 0;
	private:
		friend class Subject;
		Observer* next_ = nullptr;
	};
}
