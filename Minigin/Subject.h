#pragma once
#include <memory>
#include "Observer.h"
namespace dae {
	class Subject
	{
	public:
		void addObserver(std::shared_ptr<Observer> observer);
		void addObserver(Observer* observer);
	
		void removeAllObserver();
		void removeObserver(std::shared_ptr<Observer> observer);
		
	protected:
		void notify(const BaseComponent* entity, EventType event);

	private:
		Observer* head_ = nullptr;
		// Other stuff...
	};
}