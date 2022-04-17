#include "MiniginPCH.h"
#include "RigidbodyComponent.h"
#include "Time.h"
#include "Scene.h"
#include "GameObject.h"

void dae::RigidbodyComponent::LateUpdate()
{
	Transform& tr = m_pParent->GetTransform();
	Grid* currGrid = m_pParent->GetScene()->GetSceneGrid();
	glm::vec2 newPos;
	newPos = tr.GetPosition();

	//If is on ground move
	if (currGrid->IsHittingTerrain(glm::vec2{ tr.GetPosition().x, tr.GetPosition().y }, glm::vec2(0, -1))) {
		newPos.x += m_Velocity.x * dae::Time::GetInstance().GetDeltaTime();
		newPos.y += m_Velocity.y * dae::Time::GetInstance().GetDeltaTime();
		tr.SetPosition(newPos.x, newPos.y, 0.f);
	}
	m_Velocity = glm::vec2{ 0,0 };
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
