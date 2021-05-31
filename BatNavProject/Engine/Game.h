//
// Created by Charlotte Nicaudie on 31/05/2021.
//

#pragma once

#include "EngineIncludes.h"

namespace BatNav
{
    namespace Engine
    {
        class Game
        {
        public:
            Game(const char* windowTitle);
            virtual ~Game();

            void RunGameLoop();

        protected:
            virtual void Update(float deltaTime) = 0;
            //virtual void UpdateGUI(float deltaTime) = 0;
            virtual void Render(sf::RenderTarget& target) = 0;
            //virtual void RenderGUI(sf::RenderTarget& target) = 0;

            //====================//

            sf::RenderWindow m_Window;
        };
    }
}
