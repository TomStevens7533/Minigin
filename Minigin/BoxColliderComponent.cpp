#include "MiniginPCH.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "TillingComponent.h"
#include "SpriteComponent.h"
#include "Scene.h"

void dae::BoxColliderComponent::LateUpdate()
{
	/*glm::vec3 goPos = m_pParent->GetTransform().GetPosition();
	m_Collider->m_ColliderRect = Rectf{ goPos.x - m_Precision, goPos.y - m_Precision, m_Dimensions.x, m_Dimensions.y + m_Precision };*/
}

void dae::BoxColliderComponent::Start()
{
	TillingComponent* tillComp = m_pParent->GetComponent<TillingComponent>();
	SpriteComponent* spriteComp = m_pParent->GetComponent<SpriteComponent>();

	if (spriteComp != nullptr) {
		m_Dimensions = spriteComp->GetCurrentAnimDimensions();
		m_Dimensions.x += m_Precision;
		m_Dimensions.y += m_Precision;

	}
	if (tillComp != nullptr) {
		int tileAmount = tillComp->GetTileAmount();
		int whiteSpace = tillComp->GetWhiteSpace();
		bool isVertical = tillComp->IsVertical();

		//if gameobject has a tilling component resize collider
		if (isVertical) {
			m_Dimensions.y = (whiteSpace + m_Dimensions.y) * tileAmount ;
		}
		else
			m_Dimensions.x = (whiteSpace + m_Dimensions.x) * tileAmount;
	
		m_Dimensions.y += m_Precision;
		m_Dimensions.x += m_Precision;


	}
	//Set grid to impassable
	ColliderInfo info;
	glm::vec3 goPos = m_pParent->GetTransform().GetPosition();
	info.m_ColliderRect = Rectf{ goPos.x - m_Precision, goPos.y - m_Precision, m_Dimensions.x, m_Dimensions.y };
	info.tag = m_ColliderTag;
	m_pParent->GetScene()->AddColliderToScene(info);
}

dae::BoxColliderComponent::BoxColliderComponent(int width, int height, std::string tag, int precision)
	: m_Dimensions{width, height}, m_ColliderTag{ tag }, m_Precision{precision}
{

}

dae::BoxColliderComponent::BoxColliderComponent(std::string tag, int precision /*= 0*/) : 
	m_ColliderTag{ tag }, m_Precision{ precision }
{

}

dae::BoxColliderComponent::BoxColliderComponent(glm::vec2 dimensions, std::string tag, int precision)
	: m_Dimensions{dimensions}, m_ColliderTag{tag}, m_Precision{ precision }
{

}
