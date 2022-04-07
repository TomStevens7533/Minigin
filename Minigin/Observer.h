#pragma once
#include "BaseComponent.h"
#include <memory>
#include "EventType.h"
namespace dae {

	struct EventArgs {
		bool nothing;
	};

	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void onNotify(const BaseComponent* entity, EventType event, EventArgs* args = nullptr) = 0;
	private:
		friend class Subject;
		Observer* next_ = nullptr;
	};
}
