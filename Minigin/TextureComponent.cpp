#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <limits.h>
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"

namespace dae {



	TextureComponent::TextureComponent()
	{
	}
	void TextureComponent::SetTexture(std::shared_ptr<Texture2D> newTexture)
	{
		m_Texture.reset();
		m_Texture = newTexture;
		RenderComponent* renderComponent = (m_pParent->AddOrGetComponent<dae::RenderComponent>());

		renderComponent->SetData(m_Texture.get());

	}

	glm::vec2 TextureComponent::GetDimensions()
	{
		return m_Texture->GetDimensions();
	}

	void TextureComponent::Start()
	{
		RenderComponent* renderComponent = (m_pParent->AddOrGetComponent<dae::RenderComponent>());
		renderComponent->SetData(m_Texture.get());
	}
	TextureComponent::~TextureComponent()
	{
		m_Texture.reset();
	}
	void TextureComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

};


