//
// Created by Charlotte Nicaudie on 31/05/2021.
//

#include "GameManager.h"
#include "GameplayIncludes.h"
#include "../UI/UIManager.h"
#include "../UI/UIViewModel.h"
#include "../Engine/Event/EventTypes/ClickEvent.h"

namespace BatNav
{
    namespace Gameplay
    {
        static constexpr float SWITCH_TURN_COOLDOWN = 1.5f;
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
                , m_Players{Player(false, true, true)
                            , Player(true, false, false)}
                , m_CurrentPlayerIndex(0)
        {
            // Center the view
            sf::View gameView;
            gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.5f, 3.f));
            m_Window.setView(gameView);

            // Event listeners configuration
            Engine::EventListener<GameManager, Engine::Event> listenerEvent(this, &GameManager::OnEvent);
            Engine::EventListener<GameManager, Engine::ClickEvent> listenerClickEvent(this, &GameManager::OnEvent);
            Engine::EventManager::GetInstance()->AddListener(listenerEvent);
            Engine::EventManager::GetInstance()->AddListener(listenerClickEvent);
        }

        GameManager::~GameManager()
        {
            Engine::EventListener<GameManager, Engine::Event> listenerEvent(this, &GameManager::OnEvent);
            Engine::EventListener<GameManager, Engine::ClickEvent> listenerClickEvent(this, &GameManager::OnEvent);
            Engine::EventManager::GetInstance()->RemoveListener(listenerEvent);
            Engine::EventManager::GetInstance()->RemoveListener(listenerClickEvent);

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
                auto currentBoardIndex = GetCurrentBoardIndex();
                Board& currentBoard = m_Players[currentBoardIndex].GetBoard();
                Player& currentPlayer = m_Players[m_CurrentPlayerIndex];

                currentBoard.Update(mousePosition);

                if (m_CurrentState == GameState::PLACING_BOATS)
                {
                    static int boatPlacementCount = 0;

                    if (currentBoard.PlacedAllBoats())
                    {
                        if (++boatPlacementCount == m_Players.size())
                        {
                            LOG_INFO("The battle has started !");
                            m_CurrentState = GameState::PLAYING;
                        }

                        SwitchTurns(currentBoard);
                    }
                    else if (currentPlayer.IsRandom())
                    {
                        currentBoard.PlaceAllBoatsRandom(true);
                    }
                }
                else if (m_CurrentState == GameState::PLAYING)
                {
                    if (m_TurnTimer.getElapsedTime().asSeconds() >= TURN_TIMEOUT)
                    {
                        LOG_INFO("Turn Timeout !");
                        SwitchTurns(currentBoard);
                    }

                    if (currentPlayer.IsRandom())
                    {
                        currentBoard.AttackRandom();
                    }

                    CheckAttacks(currentBoard);

                    UI::UIViewModel::GetInstance()->SetTurnTime(m_TurnTimer.getElapsedTime().asSeconds());
                }
                else if ((m_CurrentState == GameState::SWITCHING_TURNS)
                    && (m_TurnTimer.getElapsedTime().asSeconds() >= SWITCH_TURN_COOLDOWN))
                {
                    SwitchTurns(currentBoard);
                    m_CurrentState = GameState::PLAYING;
                }
            }
        }

        unsigned long GameManager::GetCurrentBoardIndex() const
        {
            return m_CurrentState == GameState::PLACING_BOATS
                        ? m_CurrentPlayerIndex
                        : (m_CurrentPlayerIndex + 1) % m_Players.size();
        }

        void GameManager::SwitchTurns(Board& currentBoard)
        {
            LOG_DEBUG("Switching current board");

            currentBoard.ResetCurrent();
            currentBoard.ResetAttack();

            m_CurrentPlayerIndex = (m_CurrentPlayerIndex + 1) % m_Players.size();

            auto currentBoardIndex = GetCurrentBoardIndex();
            m_Players[currentBoardIndex].GetBoard().SetToCurrent();

            m_TurnTimer.restart();
        }

        void GameManager::CheckAttacks(Board& currentBoard)
        {
            if (currentBoard.WasAttacked())
            {
                LOG_INFO("Attack detected!");

                m_CurrentState = GameState::SWITCHING_TURNS;
                m_TurnTimer.restart();
            }
        }

        void GameManager::Render(sf::RenderTarget& target)
        {
            target.clear(sf::Color(0, 0, 0));

            if (m_CurrentState != GameState::NOT_STARTED)
            {
                target.draw(m_Players[GetCurrentBoardIndex()].GetBoard());
            }

            target.draw(*m_UIManager);
        }

        void GameManager::OnEvent(const Engine::Event* evnt)
        {
            const auto* clickEvent = dynamic_cast<const Engine::ClickEvent*>(evnt);

            if (clickEvent != nullptr && !clickEvent->IsRightClick())
            {
                Board& currentBoard = m_Players[GetCurrentBoardIndex()].GetBoard();
                Player& currentPlayer = m_Players[m_CurrentPlayerIndex];

                switch (m_CurrentState)
                {
                    case GameState::PLACING_BOATS:
                    {
                        currentPlayer.PlaceBoat();
                        break;
                    }

                    case GameState::PLAYING:
                    {
                        currentPlayer.Attack(currentBoard);
                        break;
                    }

                    default:
                        break;
                }
            }
            else if (evnt->GetEventType() == Engine::EventType::START_GAME)
            {
                LOG_INFO("GAME STARTED !!!");
                m_CurrentState = GameState::PLACING_BOATS;
            }
            else if (evnt->GetEventType() == Engine::EventType::END_GAME)
            {
                LOG_INFO("GAME OVER !!!");
                LOG_INFO("Player " << m_CurrentPlayerIndex << " won !");
                m_CurrentState = GameState::OVER;
            }
        }
    }
}
