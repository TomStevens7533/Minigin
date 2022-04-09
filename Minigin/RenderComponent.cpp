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

	}

	void RenderComponent::Render() const
	{
		Transform trans = m_pParent->GetTransform();
		Renderer::GetInstance().RenderTexture(*std::reinterpret_pointer_cast<Texture2D>(m_DataToRender), trans.GetPosition().x, trans.GetPosition().y);
	}

	void RenderComponent::Update()
	{

	}

	void RenderComponent::LateUpdate()
	{

	}
	void RenderComponent::SetData(std::shared_ptr<void> newData)
	{
		m_DataToRender = newData;
	}


}