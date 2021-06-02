//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#pragma once

#include <SFML/Graphics.hpp>

namespace BatNav
{
    namespace Engine
    {
        class InputManager
        {
        public:
            InputManager();

            void ManageInputEvents(const sf::Event& event);

            inline void UpdateMousePosition(const sf::Vector2f& mousePosition)
            {
                m_MousePosition = mousePosition;
            };

        private:
            sf::Clock m_MouseClickTimer;
            bool m_IsClicking;
            sf::Vector2f m_MousePosition;
        };
    }
}


