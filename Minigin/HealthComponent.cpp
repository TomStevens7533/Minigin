#include "MiniginPCH.h"
#include "HealthComponent.h"
#include <iostream>
namespace dae {
	void HealthComponent::DecreaseHealth(int healthDecrease)
	{
		m_Health -= healthDecrease;
		std::cout << "decrease health\n";
		if (m_Health <= 0) {
			//Notify observer that this entity died;
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
