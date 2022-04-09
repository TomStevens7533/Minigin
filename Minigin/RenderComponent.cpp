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
		Transform trans = m_pParent->GetTransform();
		Renderer::GetInstance().RenderTexture(*(m_DataToRender), trans.GetPosition().x, trans.GetPosition().y);
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