//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#include <cmath>
#include "Board.h"
#include "../GameplayIncludes.h"
#include "../../Engine/Event/EventTypes/ClickEvent.h"

namespace BatNav
{
    namespace Gameplay
    {
        static const sf::Vector2u BOARD_SIZE { 10, 10 };
        static const sf::Vector2u TILE_SIZE { 32, 32 };

        Board::Board(const bool isCurrent)
            : m_Board(BOARD_SIZE.x * BOARD_SIZE.y, 0)
            , m_IsCurrent(isCurrent)
            , m_WasAttacked(false)
        {
            if (!m_TileSet.loadFromFile("../Assets/tiles_test.png"))
            {
                LOG_ERROR("TileSet was not loaded correctly !");
            }

            LoadBoard();

            Engine::EventListener<Board, Engine::ClickEvent> listenerClickEvent(this, &Board::OnEvent);
            Engine::EventManager::GetInstance()->AddListener(listenerClickEvent);
        }

        Board::~Board()
        {
            Engine::EventListener<Board, Engine::ClickEvent> listenerClickEvent(this, &Board::OnEvent);
            Engine::EventManager::GetInstance()->RemoveListener(listenerClickEvent);
        }

        void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // Draw the background map
            states.transform *= getTransform(); // Apply the transform
            states.texture = &m_TileSet; // Apply the tileset texture
            target.draw(m_Vertices, states); // Draw the vertex array
        }

        void Board::LoadBoard()
        {
            // Resize the vertex array to fit the level size
            m_Vertices.clear();
            m_Vertices.setPrimitiveType(sf::Quads);
            m_Vertices.resize(static_cast<size_t>(BOARD_SIZE.x) * static_cast<size_t>(BOARD_SIZE.y) * 4);

            // Populate the vertex array, with one quad per tile
            for (unsigned int i = 0; i < BOARD_SIZE.x; ++i)
            {
                for (unsigned int j = 0; j < BOARD_SIZE.y; ++j)
                {
                    // Get the current tile number
                    const size_t boardIndex = static_cast<size_t>(i) + static_cast<size_t>(j) * static_cast<size_t>(BOARD_SIZE.y);
                    const int tileNumber = m_Board[boardIndex] ? 3 : 1;

                    // Find its position in the tileset texture
                    int tu = tileNumber % (m_TileSet.getSize().x / TILE_SIZE.x);
                    int tv = tileNumber / (m_TileSet.getSize().x / TILE_SIZE.x);

                    // Get a pointer to the current tile's quad
                    sf::Vertex* quad = &m_Vertices[boardIndex * 4];

                    // Define its 4 corners
                    quad[0].position = sf::Vector2f(static_cast<float>(i * TILE_SIZE.x), static_cast<float>(j * TILE_SIZE.y));
                    quad[1].position = sf::Vector2f(static_cast<float>((i + 1) * TILE_SIZE.x), static_cast<float>(j * TILE_SIZE.y));
                    quad[2].position = sf::Vector2f(static_cast<float>((i + 1) * TILE_SIZE.x), static_cast<float>((j + 1) * TILE_SIZE.y));
                    quad[3].position = sf::Vector2f(static_cast<float>(i * TILE_SIZE.x), static_cast<float>((j + 1) * TILE_SIZE.y));

                    // Define its 4 texture coordinates
                    quad[0].texCoords = sf::Vector2f(static_cast<float>(tu * TILE_SIZE.x), static_cast<float>(tv * TILE_SIZE.y));
                    quad[1].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * TILE_SIZE.x), static_cast<float>(tv * TILE_SIZE.y));
                    quad[2].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * TILE_SIZE.x), static_cast<float>((tv + 1) * TILE_SIZE.y));
                    quad[3].texCoords = sf::Vector2f(static_cast<float>(tu * TILE_SIZE.x), static_cast<float>((tv + 1) * TILE_SIZE.y));
                }
            }
        }

        void Board::OnEvent(const Engine::Event* evnt)
        {
            if (m_IsCurrent && !m_WasAttacked)
            {
                if (const Engine::ClickEvent* clickEvent = dynamic_cast<const Engine::ClickEvent*>(evnt))
                {
                    LOG_DEBUG("Click event received !");
                    ManageClickAttack(clickEvent->GetClickPosition());
                }
            }
        }

        void Board::ManageClickAttack(const sf::Vector2f& clickPosition)
        {
            // Check that click happened within the board limits
            if (clickPosition.x < 0 || clickPosition.x > BOARD_SIZE.x * TILE_SIZE.x
                || clickPosition.y < 0 || clickPosition.y > BOARD_SIZE.y * TILE_SIZE.y)
            {
                return;
            }

            // Convert the click position to get the tile coordinates
            const float i = floorf(clickPosition.x / static_cast<float>(TILE_SIZE.x));
            const float j = floorf(clickPosition.y / static_cast<float>(TILE_SIZE.y));
            LOG_DEBUG("Click position : " << clickPosition.x << " / " << clickPosition.y);
            LOG_DEBUG("Target tile : " << i << " / " << j);

            // Convert the the coordinates to get the index on the board
            const size_t boardIndex = static_cast<size_t>(i) + static_cast<size_t>(j) * static_cast<size_t>(BOARD_SIZE.y);

            // Mark the tile and board as attacked
            if (!m_Board[boardIndex])
            {
                m_Board[boardIndex] = true;
                m_WasAttacked = true;

                // Reload the board
                LoadBoard();
            }
        }
    }
}