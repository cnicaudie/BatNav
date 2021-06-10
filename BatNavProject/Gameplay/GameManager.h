//
// Created by Charlotte Nicaudie on 31/05/2021.
//

#pragma once

#include "../Engine/Game.h"
#include "./Board/Board.h"

namespace BatNav
{
    namespace UI
    {
        class UIManager;
    }

    namespace Gameplay
    {
        class GameManager : public Engine::Game
        {
        public:
            static GameManager* GetInstance();
            GameManager(const GameManager& gameManager) = delete;
            void operator=(const GameManager& gameManager) = delete;

            void Update(float deltaTime) override;
            void Render(sf::RenderTarget& target) override;

            //inline const bool IsGameOver() const { return m_CurrentState == GameState::OVER; }
            inline const bool IsPlacingBoats() const { return m_CurrentState == GameState::PLACING_BOATS; }
            inline const bool HasStarted() const { return m_CurrentState != GameState::NOT_STARTED; }

        private:
            GameManager();
            ~GameManager();

            void CheckAttacks();
            void SwitchCurrentBoard();

            void OnEvent(const Engine::Event* evnt);

            //====================//

            static GameManager* m_GameManager; // Singleton instance

            std::unique_ptr<UI::UIManager> m_UIManager;

            enum class GameState
            {
                NOT_STARTED     = 0,
                PLACING_BOATS   = 1,
                PLAYING         = 2,
                SWITCHING_TURNS = 3,
                OVER            = 4
            } m_CurrentState;

            Board m_BoardA;
            Board m_BoardB;

            sf::Clock m_SwitchTurnTimer;
        };
    }
}
