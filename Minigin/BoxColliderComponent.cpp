#include "MiniginPCH.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "TillingComponent.h"
#include "Scene.h"

void dae::BoxColliderComponent::LateUpdate()
{
}

void dae::BoxColliderComponent::Start()
{
	TillingComponent* tillComp = m_pParent->GetComponent<TillingComponent>();
	if (tillComp != nullptr) {
		int tileAmount = tillComp->GetTileAmount();
		int whiteSpace = tillComp->GetWhiteSpace();
		bool isVertical = tillComp->IsVertical();

		//if gameobject has a tilling component resize collider
		if (isVertical) {
			m_Dimensions.y = (whiteSpace + m_Dimensions.y) * tileAmount;
		}
		else
			m_Dimensions.x = (whiteSpace + m_Dimensions.x) * tileAmount;
	}
	//Set grid to impassable
	Grid* currGrid = m_pParent->GetScene()->GetSceneGrid();
	glm::vec3 goPos = m_pParent->GetTransform().GetPosition();
	currGrid->SetTerrain(glm::vec2{ goPos.x, goPos.y }, m_Dimensions);
}

dae::BoxColliderComponent::BoxColliderComponent(int width, int height) : m_Dimensions{width, height}
{

}

dae::BoxColliderComponent::BoxColliderComponent(glm::vec2 dimensions) : m_Dimensions{dimensions}
{

}
