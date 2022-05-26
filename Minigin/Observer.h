#pragma once
#include "BaseComponent.h"
#include <memory>
#include "EventType.h"
namespace dae {

	struct EventArgs {};
	enum EventType {
		Collision = 999
	};
	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void onNotify(const BaseComponent* entity, int event, EventArgs* args = nullptr) = 0;
	private:
		friend class Subject;
		Observer* next_ = nullptr;
	};
}
