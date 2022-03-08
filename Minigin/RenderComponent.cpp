#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
namespace dae {

	RenderComponent::RenderComponent()
	{
	
	}

	RenderComponent::~RenderComponent()
	{

	}

	void RenderComponent::Render() const
	{
		Renderer::GetInstance().RenderTexture(*std::reinterpret_pointer_cast<Texture2D>(m_DataToRender), m_Position.x, m_Position.y);
	}

	void RenderComponent::Update()
	{

	}

	void RenderComponent::LateUpdate()
	{

	}

	void RenderComponent::SetPos(const glm::vec2 pos)
	{
		m_Position = pos;
	}

	void RenderComponent::SetData(std::shared_ptr<void> newData)
	{
		m_DataToRender = newData;
	}


}