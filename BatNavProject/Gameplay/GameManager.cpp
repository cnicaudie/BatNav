//
// Created by Charlotte Nicaudie on 31/05/2021.
//

#include "GameManager.h"
#include "GameplayIncludes.h"
#include "../UI/UIManager.h"

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
                , m_UIManager{ std::make_unique<UI::UIManager>(&m_Window) }
                , m_CurrentState(GameState::NOT_STARTED)
                , m_BoardA(true)
                , m_BoardB(false)
        {
            // Center the view
            sf::View gameView;
            gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.5f, 3.f));
            m_Window.setView(gameView);

            // TODO : Remove that when integrating a main menu
            m_CurrentState = GameState::PLACING_BOATS;
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
            m_UIManager->Update(deltaTime);

            m_BoardB.Update(mousePosition);
            m_BoardA.Update(mousePosition);

            if (m_CurrentState == GameState::PLACING_BOATS)
            {
                if (m_BoardA.IsCurrent() && m_BoardA.PlacedAllBoats())
                {
                    SwitchCurrentBoard();
                }
                else if (m_BoardB.IsCurrent() && m_BoardB.PlacedAllBoats())
                {
                    SwitchCurrentBoard();
                    m_CurrentState = GameState::PLAYING;
                }
            }
            else if (m_CurrentState == GameState::PLAYING)
            {
                CheckAttacks();
            }
            else if ((m_CurrentState == GameState::SWITCHING_TURNS)
                && (m_SwitchTurnTimer.getElapsedTime().asSeconds() >= SWITCH_TURN_COOLDOWN))
            {
                SwitchCurrentBoard();
                m_CurrentState = GameState::PLAYING;
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

            target.draw(*m_UIManager);
        }
    }
}
