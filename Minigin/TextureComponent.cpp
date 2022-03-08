#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <limits.h>
#include "ResourceManager.h"
#include "Renderer.h"

namespace dae {



	TextureComponent::TextureComponent()
	{
	

		m_RenderComponent = std::make_unique<RenderComponent>();
	}

	TextureComponent::~TextureComponent()
	{
		m_Texture.reset();
		m_RenderComponent.reset();
	}


	void TextureComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
		m_RenderComponent->SetData(m_Texture);
	}

	void TextureComponent::SetPosition(const glm::vec2& pos)
	{
		m_RenderComponent->SetPos(pos);
	}

	void TextureComponent::Render() const
	{
		m_RenderComponent->Render();
	}

	void TextureComponent::Update()
	{

	}

	void TextureComponent::LateUpdate()
	{

	}

};


