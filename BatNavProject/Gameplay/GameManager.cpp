//
// Created by Charlotte Nicaudie on 31/05/2021.
//

#include "GameManager.h"
#include "GameplayIncludes.h"
#include "../UI/UIManager.h"
#include "../UI/UIViewModel.h"

namespace BatNav
{
    namespace Gameplay
    {
        static constexpr float SWITCH_TURN_COOLDOWN = 1.f;
        static constexpr float TURN_TIMEOUT = 20.f;

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
                , m_Boards{ Board(true, true)
                           , Board(false, false) }
                , m_CurrentBoardIndex(0)
        {
            // Center the view
            sf::View gameView;
            gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.5f, 3.f));
            m_Window.setView(gameView);

            // Event listeners configuration
            Engine::EventListener<GameManager, Engine::Event> listenerEvent(this, &GameManager::OnEvent);
            Engine::EventManager::GetInstance()->AddListener(listenerEvent);
        }

        GameManager::~GameManager()
        {
            Engine::EventListener<GameManager, Engine::Event> listenerEvent(this, &GameManager::OnEvent);
            Engine::EventManager::GetInstance()->RemoveListener(listenerEvent);

            delete m_GameManager;
        }

        void GameManager::Update(float deltaTime)
        {
            const sf::Vector2f mousePosition = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));

            Engine::EventManager::GetInstance()->Update();
            m_InputManager->UpdateMousePosition(mousePosition);
            m_UIManager->Update(deltaTime);

            if (m_CurrentState != GameState::NOT_STARTED)
            {
                m_Boards[m_CurrentBoardIndex].Update(mousePosition);

                if (m_CurrentState == GameState::PLACING_BOATS)
                {
                    static int boatPlacementCount = 0;

                    if (m_Boards[m_CurrentBoardIndex].PlacedAllBoats())
                    {
                        SwitchCurrentBoard();

                        ++boatPlacementCount;

                        if (boatPlacementCount == m_Boards.size())
                        {
                            m_CurrentState = GameState::PLAYING;
                        }
                    }
                }
                else if (m_CurrentState == GameState::PLAYING)
                {
                    if (m_TurnTimer.getElapsedTime().asSeconds() >= TURN_TIMEOUT)
                    {
                        LOG_INFO("Turn Timeout !");
                        SwitchCurrentBoard();
                    }

                    CheckAttacks();

                    UI::UIViewModel::GetInstance()->SetTurnTime(m_TurnTimer.getElapsedTime().asSeconds());
                }
                else if ((m_CurrentState == GameState::SWITCHING_TURNS)
                    && (m_TurnTimer.getElapsedTime().asSeconds() >= SWITCH_TURN_COOLDOWN))
                {
                    SwitchCurrentBoard();
                    m_CurrentState = GameState::PLAYING;
                }
            }
        }

        void GameManager::SwitchCurrentBoard()
        {
            LOG_DEBUG("Switching current board");

            m_Boards[m_CurrentBoardIndex].ResetCurrent();
            m_Boards[m_CurrentBoardIndex].ResetAttack();
            m_CurrentBoardIndex = (m_CurrentBoardIndex + 1) % m_Boards.size();
            m_Boards[m_CurrentBoardIndex].SetToCurrent();

            m_TurnTimer.restart();
        }

        void GameManager::CheckAttacks()
        {
            if (m_Boards[m_CurrentBoardIndex].WasAttacked())
            {
                LOG_DEBUG("Attack detected!");

                m_CurrentState = GameState::SWITCHING_TURNS;
                m_TurnTimer.restart();
            }
        }

        void GameManager::Render(sf::RenderTarget& target)
        {
            target.clear(sf::Color(0, 0, 0));

            if (m_CurrentState != GameState::NOT_STARTED)
            {
                target.draw(m_Boards[m_CurrentBoardIndex]);
            }

            target.draw(*m_UIManager);
        }

        void GameManager::OnEvent(const Engine::Event* evnt)
        {
            if (evnt->GetEventType() == Engine::EventType::START_GAME)
            {
                m_CurrentState = GameState::PLACING_BOATS;
            }
            else if (evnt->GetEventType() == Engine::EventType::END_GAME)
            {
                LOG_INFO("GAME OVER !!!");
                m_CurrentState = GameState::OVER;
            }
        }
    }
}
