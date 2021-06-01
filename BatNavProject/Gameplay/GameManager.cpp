//
// Created by Charlotte Nicaudie on 31/05/2021.
//

#include "GameManager.h"
#include "GameplayIncludes.h"

namespace BatNav
{
    namespace Gameplay
    {
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
                , m_IsPlayerATurn(true)
                , m_BoardA()
                , m_BoardB()
        {
            m_Shape.setRadius(40.f);
            m_Shape.setPosition(100.f, 100.f);
            m_Shape.setFillColor(sf::Color::Cyan);

            m_BoardA.LoadBoard();

            // Center the view
            sf::View gameView;
            gameView.setViewport(sf::FloatRect(0.25f, 0.25, 1.5f, 1.5f));
            m_Window.setView(gameView);
        }

        GameManager::~GameManager()
        {
            delete m_GameManager;
        }


        void GameManager::Update(float deltaTime)
        {
            m_InputManager->UpdateMousePosition(m_Window);
        }

        void GameManager::Render(sf::RenderTarget& target)
        {
            target.clear(sf::Color(0, 0, 0));
            target.draw(m_Shape);

            m_IsPlayerATurn
                ? target.draw(m_BoardA)
                : target.draw(m_BoardB);
        }
    }
}
