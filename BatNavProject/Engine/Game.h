//
// Created by Charlotte Nicaudie on 31/05/2021.
//

#pragma once

#include "EngineIncludes.h"
#include "./Input/InputManager.h"

namespace BatNav
{
    namespace Engine
    {
        class InputManager;

        class Game
        {
        public:
            Game(const char* windowTitle);
            virtual ~Game();

            void RunGameLoop();

        protected:
            virtual void Update(float deltaTime) = 0;
            virtual void Render(sf::RenderTarget& target) = 0;

            //====================//

            sf::RenderWindow m_Window;
            std::shared_ptr<InputManager> m_InputManager;
        };
    }
}
