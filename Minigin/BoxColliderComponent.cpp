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
		m_Dimensions.x += m_Precision * 2.f;
		m_Dimensions.y += m_Precision *2.f;

	}
	else if (texComp != nullptr) {

		m_Dimensions =  texComp->GetDimensions();
		m_Dimensions.y += m_Precision * 2.f;
		m_Dimensions.x += m_Precision * 2.f;


	}
	ColliderInfo info;
	glm::vec3 goPos = GetAttachedGameObject()->RelativePositionToParent();
	info.m_ColliderRect = Rectf{ goPos.x - m_Precision, goPos.y - m_Precision, m_Dimensions.x, m_Dimensions.y };
	info.tag = m_ColliderTag;
	info.m_pAttachedGameObject = m_pParent;
	info.m_OverlapStayFunc = std::bind(&BoxColliderComponent::OnOverlapStay, this, std::placeholders::_1);
	info.m_OverlapEnterFunc = std::bind(&BoxColliderComponent::OnOverlapEnter, this, std::placeholders::_1);
	info.m_OverlapExitFunc = std::bind(&BoxColliderComponent::OnOverlaExit, this, std::placeholders::_1);
	m_pColliderInfo = m_pParent->GetScene()->AddColliderToScene(info);


}

void dae::BoxColliderComponent::DisableCollider()
{
	m_pColliderInfo->IsEnabled = false;
}

void dae::BoxColliderComponent::EnableCollider()
{
	m_pColliderInfo->IsEnabled = true;
}

const dae::ColliderInfo& dae::BoxColliderComponent::GetColliderInfo() const
{
	return *m_pColliderInfo.get();
}

void dae::BoxColliderComponent::OnOverlapStay(const std::shared_ptr<ColliderInfo> otherCollider)
{
	CollisionArgs args{};
	args.info = *otherCollider;
	//Send to observers
	notify(this, EventType::OnCollisionStay, &args);
}

void dae::BoxColliderComponent::OnOverlapEnter(const std::shared_ptr<ColliderInfo> otherCollider)
{
	CollisionArgs args{};
	args.info = *otherCollider;
	//Send to observers
	notify(this, EventType::OnCollisionEnter, &args);
}

void dae::BoxColliderComponent::OnOverlaExit(const std::shared_ptr<ColliderInfo> otherCollider)
{
	CollisionArgs args{};
	args.info = *otherCollider;
	//Send to observers
	notify(this, EventType::OnCollisionExit, &args);
}

dae::BoxColliderComponent::BoxColliderComponent(int width, int height, std::string tag, int precision)
	: m_Dimensions{width, height}, m_ColliderTag{ tag }, m_Precision{precision}
{

}

dae::BoxColliderComponent::~BoxColliderComponent()
{

}

void dae::BoxColliderComponent::Render() const
{
	if (m_pColliderInfo) {
		SDL_Rect rect;
		rect.w = (int)m_pColliderInfo->m_ColliderRect.width;
		rect.h = (int)m_pColliderInfo->m_ColliderRect.height;
		glm::vec3 goPos = GetAttachedGameObject()->RelativePositionToParent();
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
		glm::vec3 goPos = GetAttachedGameObject()->RelativePositionToParent();
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
