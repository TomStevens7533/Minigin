#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include <SDL_ttf.h>

namespace dae {

	TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font)
		: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_TextTexture(nullptr)
	{

	}
	TextComponent::~TextComponent()
	{
		m_Font.reset();
		m_TextTexture.reset();
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}

	void TextComponent::SetPosition(const glm::vec2& pos)
	{
		m_RenderComponent.SetPos(pos);
	}

	void TextComponent::Render() const
	{
		if (m_TextTexture != nullptr)
		{
			m_RenderComponent.Render();
		}
	}

	void TextComponent::Update()
	{
		if (m_NeedsUpdate)
		{
			const SDL_Color color = { 255,255,255 }; // only white text is supported now
			const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
			if (surf == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
			if (texture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);
			m_TextTexture = std::make_shared<Texture2D>(texture);
			m_NeedsUpdate = false;
			m_RenderComponent.SetData(m_TextTexture);
		}
	}

	void TextComponent::LateUpdate()
	{

	}



}
