#include "MiniginPCH.h"
#include "BoxCollider.h"

dae::BoxColliderComponent::BoxColliderComponent()
{

}

void dae::BoxColliderComponent::LateUpdate()
{
}

dae::BoxColliderComponent::BoxColliderComponent(int width, int height) : m_Dimensions{width, height}
{

}
