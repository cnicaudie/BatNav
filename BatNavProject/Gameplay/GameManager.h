//
// Created by Charlotte Nicaudie on 31/05/2021.
//

#pragma once

#include "../Engine/Game.h"

namespace BatNav
{
    namespace Gameplay
    {
        class GameManager : public Engine::Game
        {
        public:
            static GameManager* GetInstance();
            GameManager(const GameManager& gameManager) = delete;
            void operator=(const GameManager& gameManager) = delete;

            void Update(float deltaTime) override;
            //void UpdateGUI(float deltaTime) override;
            void Render(sf::RenderTarget& target) override;
            //void RenderGUI(sf::RenderTarget& target) override;

            inline const bool IsGameOver() const { return m_CurrentState == GameState::OVER; }

        private:
            GameManager();
            ~GameManager();

            //====================//

            static GameManager* m_GameManager; // Singleton instance

            enum class GameState
            {
                NOT_STARTED = 0,
                PLAYING     = 1,
                OVER        = 2
            } m_CurrentState;

            sf::CircleShape m_Shape; // Test shape
        };
    }
}
