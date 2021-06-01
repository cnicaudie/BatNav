//
// Created by Charlotte Nicaudie on 31/05/2021.
//

#include "GameManager.h"

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
        }

        GameManager::~GameManager()
        {
            delete m_GameManager;
        }


        void GameManager::Update(float deltaTime)
        {
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
