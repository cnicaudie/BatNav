//
// Created by Charlotte Nicaudie on 09/06/2021.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../Engine/Event/EventTypes/Event.h"
#include "Button.h"

namespace BatNav
{
    namespace UI
    {
        class UIManager : public sf::Drawable
        {
        public:
            UIManager(sf::RenderWindow* window);
            ~UIManager();

            void Update(float deltaTime);
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        private:
            void InitTexts(const sf::Vector2f& WINDOW_CENTER);
            void InitButtons(const sf::Vector2f& WINDOW_CENTER);

            void UpdateTexts();
            void ManageButtons();

            void OnEvent(const Engine::Event* evnt);

            //====================//

            sf::RenderWindow* m_Window;
            //sf::View m_GUIView;

            sf::Font m_MainFont;

            // === In Game UI
            // TODO : Score ?

            // === Main Menu
            bool m_ToggleMainMenu;
            Button m_StartButton;
            Button m_CloseButton;
            sf::Text m_MainTitle;

            // === Boat Placement Menu
            bool m_ToggleBoatPlacementMenu;
            Button m_RandomButton;
            Button m_ConfirmButton;

            // === End Game Text
            sf::Text m_EndGameText;
        };
    }
}


