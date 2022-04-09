#include "MiniginPCH.h"
#include "RigidbodyComponent.h"
#include "Time.h"
#include "GameObject.h"

void dae::RigidbodyComponent::LateUpdate()
{
	Transform& tr = m_pParent->GetTransform();
	glm::vec2 newPos;
	newPos = tr.GetPosition();
	newPos.x += m_Velocity.x * dae::Time::GetInstance().GetDeltaTime();
	newPos.y += m_Velocity.y * dae::Time::GetInstance().GetDeltaTime();
	tr.SetPosition(newPos.x, newPos.y, 0.f);
	std::cout << m_pParent->GetTransform().GetPosition().x << std::endl;
}

void dae::RigidbodyComponent::AddVelocity(float x, float y)
{
	m_Velocity.x += x;
	m_Velocity.y += y;
}

void dae::RigidbodyComponent::SetVelocity(float x, float y)
{
	m_Velocity.x = x;
	m_Velocity.y = y;
}

void dae::RigidbodyComponent::SetVelocityX(float x)
{
	m_Velocity.x = x;
}

void dae::RigidbodyComponent::SetVelocityY(float y)
{
	m_Velocity.y = y;
}
