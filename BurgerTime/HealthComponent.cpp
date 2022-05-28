#include "MiniginPCH.h"
#include "HealthComponent.h"
#include <iostream>
#include "EventType.h"

using namespace Burger;
HealthComponent::HealthComponent(int health, int lives) : m_Health{ health }, m_Lives{ lives } {}

void HealthComponent::Start()
{
	HealthArgs args;
	args.lives = m_Lives;
	args.health = m_Health;
	notify(this, PepperEvent::ENTITY_DIED, &args);
}

void HealthComponent::DecreaseHealth(int healthDecrease)
{
	m_Health -= healthDecrease;

	if (m_Health <= 0) {
		//Notify observers that this entity died;
		--m_Lives;

		if (m_Lives <= 0)
			m_IsDeath = true;

		HealthArgs args;
		args.lives = m_Lives;
		args.health = m_Health;
		notify(this, PepperEvent::ENTITY_DIED, &args);
	}
}

void HealthComponent::IncreaseHealth(int healthIncrease)
{
	m_Health += healthIncrease;

	HealthArgs args;
	args.lives = m_Lives;
	args.health = m_Health;
	notify(this, PepperEvent::HEALTH_SET, &args);
}

int  HealthComponent::GetHealth() const
{
	return m_Health;
}

void HealthComponent::SetHealth(int newHealth)
{
	m_Health = newHealth;


	HealthArgs args;
	args.lives = m_Lives;
	args.health = m_Health;
	notify(this, PepperEvent::HEALTH_SET, &args);

}

int HealthComponent::GetLives() const
{
	return m_Lives;
}

void HealthComponent::SetLives(int lives)
{
	m_Lives = lives;

	HealthArgs args;
	args.lives = m_Lives;
	args.health = m_Health;
	notify(this, PepperEvent::HEALTH_SET, &args);
}

