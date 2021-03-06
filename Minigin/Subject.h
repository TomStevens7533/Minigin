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
		void removeObserver(Observer* observer);
		
	protected:
		void notify(const BaseComponent* entity, int event, EventArgs* args =  nullptr);
	private:
		Observer* head_ = nullptr;
	};
}