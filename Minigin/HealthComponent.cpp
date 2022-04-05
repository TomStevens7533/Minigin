#include "MiniginPCH.h"
#include "HealthComponent.h"
#include <iostream>
namespace dae {
	void HealthComponent::DecreaseHealth(int healthDecrease)
	{
		m_Health -= healthDecrease;
		if (m_Health <= 0) {
			//Notify observers that this entity died;
			notify(this, EventType::ENTITY_DIED);
			//EventManager::GetInstance().ThrowEvent(EventType::ENTITY_DIED);
		}
	}	 
		 
	void HealthComponent::IncreateHealth(int healthIncrease)
	{	 
		m_Health += healthIncrease;
	}	 
		 
	int  HealthComponent::GetHealth() const
	{
		return m_Health;
	}

	void HealthComponent::SetHealth(int newHealth)
	{
		m_Health = newHealth;
	}

}
