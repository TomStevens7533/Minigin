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
	void TextureComponent::Start()
	{
		m_pRenderComponent = (m_pParent->AddOrGetComponent<dae::RenderComponent>());
		m_pRenderComponent->SetData(m_Texture.get());
	}
	TextureComponent::~TextureComponent()
	{
		m_Texture.reset();
	}
	void TextureComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

	void TextureComponent::Render() const
	{
		m_pRenderComponent->Render();
	}

	void TextureComponent::Update()
	{

	}

	void TextureComponent::LateUpdate()
	{

	}

};


