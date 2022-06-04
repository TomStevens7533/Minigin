#include "MiniginPCH.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "Renderer.h"


dae::BoxColliderComponent::BoxColliderComponent(std::string tag, int precision /*= 0*/) :
	m_ColliderTag{ tag }, m_Precision{ precision }
{

}

void dae::BoxColliderComponent::Start()
{
	if (m_pColliderInfo != nullptr)
		m_pParent->GetScene()->RemoveCollider(m_pColliderInfo);

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
	ColliderCallbacks callback;

	callback.OverlapEnterFunc = std::bind(&BoxColliderComponent::OnOverlapEnter, this, std::placeholders::_1);
	callback.OverlapStayFunc = std::bind(&BoxColliderComponent::OnOverlapStay, this, std::placeholders::_1);
	callback.OverlopExitFunc = std::bind(&BoxColliderComponent::OnOverlaExit, this, std::placeholders::_1);

	ColliderInfo info{callback};

	glm::vec3 goPos = GetAttachedGameObject()->RelativePositionToParent();
	info.m_ColliderRect = Rectf{ goPos.x - m_Precision, goPos.y - m_Precision, m_Dimensions.x, m_Dimensions.y };
	info.tag = m_ColliderTag;
	info.m_pAttachedGameObject = m_pParent;
	m_pColliderInfo = m_pParent->GetScene()->AddColliderToScene(info);


}

void dae::BoxColliderComponent::DisableCollider()
{
	//Clear overlapping colliders
	m_pColliderInfo->m_OverlappingColliders.clear();

	m_pColliderInfo->IsEnabled = false;
}

void dae::BoxColliderComponent::EnableCollider()
{
	m_pColliderInfo->IsEnabled = true;
}

void dae::BoxColliderComponent::AddListener(ColliderCallbacks otherComp)
{
	m_RegisteredListeners.push_back(otherComp);

}

void dae::BoxColliderComponent::RemoveListender(ColliderCallbacks otherComp)
{
	//TODO ADD == operator to callback
	//m_RegisteredListeners.erase(std::remove(m_RegisteredListeners.begin(), m_RegisteredListeners.end(), otherComp));
}

void dae::BoxColliderComponent::SetNewWidth(float size)
{
	m_pColliderInfo->m_ColliderRect.width = size;
}

void dae::BoxColliderComponent::SetNewHeight(float size)
{
	m_pColliderInfo->m_ColliderRect.height = size;
}

void dae::BoxColliderComponent::SetNewPos(glm::vec2 pos)
{
	m_pColliderInfo->m_ColliderRect.x = pos.x;
	m_pColliderInfo->m_ColliderRect.y = pos.y;
	//if position is set manually make it static
	m_ColType = BoxColliderType::STATIC;
}

const dae::ColliderInfo& dae::BoxColliderComponent::GetColliderInfo() const
{
	return *m_pColliderInfo.get();
}

void dae::BoxColliderComponent::OnOverlapStay(const std::shared_ptr<ColliderInfo> otherCollider)
{
	for (size_t i = 0; i < m_RegisteredListeners.size(); i++)
	{
		if (m_RegisteredListeners[i].OverlapStayFunc != nullptr)
			m_RegisteredListeners[i].OverlapStayFunc(otherCollider);
	}

}

void dae::BoxColliderComponent::OnOverlapEnter(const std::shared_ptr<ColliderInfo> otherCollider)
{
	for (size_t i = 0; i < m_RegisteredListeners.size(); i++)
	{
		if (m_RegisteredListeners[i].OverlapEnterFunc != nullptr)
			m_RegisteredListeners[i].OverlapEnterFunc(otherCollider);
	}
}

void dae::BoxColliderComponent::OnOverlaExit(const std::shared_ptr<ColliderInfo> otherCollider)
{
	for (size_t i = 0; i < m_RegisteredListeners.size(); i++)
	{
		if(m_RegisteredListeners[i].OverlopExitFunc != nullptr)
			m_RegisteredListeners[i].OverlopExitFunc(otherCollider);
	}
}
dae::BoxColliderComponent::~BoxColliderComponent()
{
	GetAttachedGameObject()->GetScene()->RemoveCollider(m_pColliderInfo);
}

void dae::BoxColliderComponent::Render() const
{

#ifdef _DEBUG
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
#endif // _DEBUG

	
	

}

void dae::BoxColliderComponent::Update()
{
	if (m_pColliderInfo != nullptr && m_ColType == BoxColliderType::DYNAMIC) {
		//Update position of BoxCollider
		glm::vec3 goPos = GetAttachedGameObject()->RelativePositionToParent();
		m_pColliderInfo->m_ColliderRect.x = goPos.x - m_Precision;
		m_pColliderInfo->m_ColliderRect.y = goPos.y - m_Precision;
	}
}

