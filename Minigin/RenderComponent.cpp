#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
namespace dae {

	RenderComponent::RenderComponent()
	{
	
	}

	RenderComponent::~RenderComponent()
	{
		m_DataToRender = nullptr;
	}

	void RenderComponent::Render() const
	{
		glm::vec3 relativePos = GetAttachedGameObject()->RelativePositionToParent();
		Renderer::GetInstance().RenderTexture(*(m_DataToRender), relativePos.x, relativePos.y);
	}

	void RenderComponent::Update()
	{
	}

	void RenderComponent::LateUpdate()
	{

	}
	void RenderComponent::SetData(Texture2D* newData)
	{
		m_DataToRender = newData;
	}


}