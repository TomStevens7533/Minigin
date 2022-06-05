#pragma once
#include "BaseComponent.h"
#include <memory>
#include "Font.h"
#include <string>
#include "glm/glm.hpp"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "Observer.h"
#include "Subject.h"

namespace dae {
	class TextComponent final: public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font>& font, glm::vec3 color = {255, 255, 255});
		~TextComponent();

		void SetText(const std::string& text);

		void Render() const override;
		void Update() override;
		void FixedUpdate() override;
		virtual void Start() override;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		RenderComponent* m_pRenderComponent;

		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;

		bool m_NeedsUpdate;
		std::string m_Text;
		glm::vec3 m_Color;

	};
}


