//
// Created by Charlotte Nicaudie on 09/06/2021.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../Engine/Event/EventTypes/Event.h"

namespace BatNav
{
    namespace UI
    {
        class Button : public sf::Drawable
        {
        public:
            Button(const sf::Vector2f& size);
            ~Button();

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            inline const void SetButtonPosition(const sf::Vector2f& centerPosition) { m_ButtonRect.setPosition(centerPosition); };
            inline const void SetButtonTextFont(const sf::Font& font) { m_ButtonText.setFont(font); };
            inline const void SetButtonTextString(const std::string& text) { m_ButtonText.setString(text); };
            inline const void SetButtonTextPosition(const sf::Vector2f& centerPosition)
            {
                float textWidth = m_ButtonText.getGlobalBounds().width;
                float textHeight = m_ButtonText.getGlobalBounds().height;

                // Center the text on the button
                m_ButtonText.setPosition({
                                                 centerPosition.x - (textWidth / 2.f),
                                                 centerPosition.y - textHeight
                                         });
            }

            inline const bool WasClicked() const { return m_WasClicked; };
            inline void ResetClickStatus() { m_WasClicked = false; };

        private:
            void OnEvent(const Engine::Event* evnt);

            inline void CheckClick(const sf::Vector2f& clickPosition)
            {
                m_WasClicked = m_ButtonRect.getGlobalBounds().contains(clickPosition);
            };

            //====================//

            sf::RectangleShape m_ButtonRect;
            sf::Text m_ButtonText;

            bool m_WasClicked;
        };
    }
}