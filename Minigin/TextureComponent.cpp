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
		m_RenderComponent.reset(m_pParent->AddOrGetComponent<dae::RenderComponent>());
		m_RenderComponent->SetData(m_Texture);
	}
	TextureComponent::~TextureComponent()
	{
		m_Texture.reset();
		m_RenderComponent.reset();
	}


	void TextureComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
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


