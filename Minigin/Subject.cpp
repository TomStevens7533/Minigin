#include "MiniginPCH.h"
#include "Subject.h"

void dae::Subject::addObserver(std::shared_ptr<Observer> observer)
{
	

	observer->next_ = head_;
	head_ = observer.get();
	
}

void dae::Subject::addObserver(Observer* observer)
{
	observer->next_ = head_;
	head_ = observer;
}

void dae::Subject::removeAllObserver()
{
	while (head_ != nullptr)
	{
		auto temp = head_->next_;
		head_ = nullptr;

		head_ = temp;
	}
}

void dae::Subject::removeObserver(std::shared_ptr<Observer> observer)
{
	Observer* interPointer = observer.get();
	if (head_ == interPointer)
	{
		head_ = interPointer->next_;
		interPointer->next_ = nullptr;
		return;
	}

	Observer* current = head_;
	while (current != nullptr)
	{
		if (current->next_ == interPointer)
		{
			current->next_ = interPointer->next_;
			interPointer->next_ = nullptr;
			return;
		}

		current = current->next_;
	}
}

void dae::Subject::notify(const BaseComponent* entity, EventType event)
{
	Observer* observer = head_;
	while (observer != nullptr)
	{
		observer->onNotify(entity, event);
		observer = observer->next_;
	}
}
