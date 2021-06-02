//
// Created by Charlotte Nicaudie on 31/05/2021.
//

#include "GameManager.h"
#include "GameplayIncludes.h"

namespace BatNav
{
    namespace Gameplay
    {
        static constexpr float SWITCH_TURN_COOLDOWN = 1.f;

        GameManager* GameManager::m_GameManager = nullptr;

        GameManager* GameManager::GetInstance()
        {
            if (m_GameManager == nullptr)
            {
                m_GameManager = new GameManager();
            }

            return m_GameManager;
        }

        GameManager::GameManager()
                : Game{ "BatNav (WIP)" }
                , m_CurrentState(GameState::NOT_STARTED)
                , m_BoardA(true)
                , m_BoardB(false)
        {
            // Center the view
            sf::View gameView;
            gameView.setViewport(sf::FloatRect(0.25f, 0.25, 1.5f, 1.5f));
            m_Window.setView(gameView);

            // TODO : Remove that when integrating a main menu
            m_CurrentState = GameState::PLAYING;
        }

        GameManager::~GameManager()
        {
            delete m_GameManager;
        }

        void GameManager::Update(float deltaTime)
        {
            const sf::Vector2f mousePosition = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));

            Engine::EventManager::GetInstance()->Update();
            m_InputManager->UpdateMousePosition(mousePosition);

            if (m_CurrentState == GameState::PLAYING)
            {
                m_BoardB.Update(mousePosition);
                m_BoardA.Update(mousePosition);

                CheckAttacks();
            }
            else if ((m_CurrentState == GameState::SWITCHING_TURNS)
                && (m_SwitchTurnTimer.getElapsedTime().asSeconds() >= SWITCH_TURN_COOLDOWN))
            {
                SwitchCurrentBoard();
            }
        }

        void GameManager::SwitchCurrentBoard()
        {
            LOG_DEBUG("Switching current board");

            if (m_BoardA.IsCurrent())
            {
                m_BoardA.ResetAttack();
                m_BoardA.ResetCurrent();
                m_BoardB.SetToCurrent();
            }
            else if (m_BoardB.IsCurrent())
            {
                m_BoardB.ResetAttack();
                m_BoardB.ResetCurrent();
                m_BoardA.SetToCurrent();
            }

            m_CurrentState = GameState::PLAYING;
        }

        void GameManager::CheckAttacks()
        {
            if (m_BoardA.WasAttacked() || m_BoardB.WasAttacked())
            {
                LOG_DEBUG("Attack detected!");

                m_CurrentState = GameState::SWITCHING_TURNS;
                m_SwitchTurnTimer.restart();
            }
        }

        void GameManager::Render(sf::RenderTarget& target)
        {
            target.clear(sf::Color(0, 0, 0));

            if (m_BoardA.IsCurrent())
            {
                target.draw(m_BoardA);
            }
            else if (m_BoardB.IsCurrent())
            {
                target.draw(m_BoardB);
            }
        }
    }
}
