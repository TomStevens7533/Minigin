#include "MiniginPCH.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "Renderer.h"

void dae::BoxColliderComponent::LateUpdate()
{

}

void dae::BoxColliderComponent::Start()
{
	SpriteComponent* spriteComp = m_pParent->GetComponent<SpriteComponent>();
	TextureComponent* texComp = m_pParent->GetComponent<TextureComponent>();

	if (spriteComp != nullptr) {
		m_Dimensions = spriteComp->GetCurrentAnimDimensions();
		m_Dimensions.x += m_Precision;
		m_Dimensions.y += m_Precision;

	}
	else if (texComp != nullptr) {

		m_Dimensions =  texComp->GetDimensions();
		m_Dimensions.y += m_Precision;
		m_Dimensions.x += m_Precision;


	}
	ColliderInfo info;
	glm::vec3 goPos = m_pParent->GetTransform().GetPosition();
	info.m_ColliderRect = Rectf{ goPos.x - m_Precision, goPos.y - m_Precision, m_Dimensions.x, m_Dimensions.y };
	info.tag = m_ColliderTag;
	info.m_pAttachedGameObject = m_pParent;
	m_pColliderInfo =  m_pParent->GetScene()->AddColliderToScene(info);
}

const std::shared_ptr<dae::ColliderInfo> dae::BoxColliderComponent::GetColliderInfo() const
{
	return m_pColliderInfo;
}

dae::BoxColliderComponent::BoxColliderComponent(int width, int height, std::string tag, int precision)
	: m_Dimensions{width, height}, m_ColliderTag{ tag }, m_Precision{precision}
{

}

void dae::BoxColliderComponent::Render() const
{
	if (m_pColliderInfo) {
		SDL_Rect rect;
		rect.w = (int)m_pColliderInfo->m_ColliderRect.width;
		rect.h = (int)m_pColliderInfo->m_ColliderRect.height;
		glm::vec3 goPos = m_pParent->GetTransform().GetPosition();
		rect.x = (int)m_pColliderInfo->m_ColliderRect.x;
		rect.y = (int)m_pColliderInfo->m_ColliderRect.y;
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);

		SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(),
			&rect);
	}
	

}

void dae::BoxColliderComponent::Update()
{
	if (m_pColliderInfo != nullptr) {
		//Update position of BoxCollider
		glm::vec3 goPos = m_pParent->GetTransform().GetPosition();
		m_pColliderInfo->m_ColliderRect.x = goPos.x - m_Precision;
		m_pColliderInfo->m_ColliderRect.y = goPos.y - m_Precision;
	}
}

dae::BoxColliderComponent::BoxColliderComponent(std::string tag, int precision /*= 0*/) : 
	m_ColliderTag{ tag }, m_Precision{ precision }
{

}

dae::BoxColliderComponent::BoxColliderComponent(glm::vec2 dimensions, std::string tag, int precision)
	: m_Dimensions{dimensions}, m_ColliderTag{tag}, m_Precision{ precision }
{

}
