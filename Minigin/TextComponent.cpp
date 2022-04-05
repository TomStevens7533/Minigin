#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include <SDL_ttf.h>

namespace dae {

	TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, glm::vec3 color)
		: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_TextTexture(nullptr), m_Color(color)
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
			const SDL_Color color = { static_cast<uint8_t>(m_Color.x), static_cast<uint8_t>(m_Color.y) , static_cast<uint8_t>(m_Color.z)}; // only white text is supported now
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

	void TextComponent::onNotify(const BaseComponent*, EventType event)
	{
		switch (event)
		{
		case dae::EventType::ENTITY_DIED:
			m_Text = std::to_string(std::stoi(m_Text) - 1);
			m_NeedsUpdate = true;
			break;
		case dae::EventType::SCORE_INCREASE:
				m_Text =std::to_string(std::stoi(m_Text) + 100);
				m_NeedsUpdate = true;
				if(std::stoi(m_Text) > 500)
					notify(this, EventType::WIN_GAME);
				break;
		default:
			break;
		}
	}



}
