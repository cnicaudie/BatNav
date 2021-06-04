//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#include <cmath>
#include "Board.h"
#include "../GameManager.h"
#include "../../Engine/Event/EventTypes/ClickEvent.h"

namespace BatNav
{
    namespace Gameplay
    {
        static const sf::Vector2u BOARD_SIZE { 10, 10 };
        static const sf::Vector2u TILE_SIZE { 32, 32 };

        Board::Board(const bool isCurrent)
            : m_Board(BOARD_SIZE.x * BOARD_SIZE.y, TileType::WATER)
            , m_Boats(5)
            , m_IsCurrent(isCurrent)
            , m_WasAttacked(false)
            , m_CanPlaceBoat(false)
            , m_PlacedAllBoats(false)
            , m_SelectedBoatIndex(0)
            , m_SelectedTileIndex(0)
        {
            // Board loading
            if (!m_TileSet.loadFromFile("../Assets/tiles_test.png"))
            {
                LOG_ERROR("TileSet was not loaded correctly !");
            }

            LoadBoard();

            // Boats preparation
            InitBoats();

            // Event listeners configuration
            Engine::EventListener<Board, Engine::ClickEvent> listenerClickEvent(this, &Board::OnEvent);
            Engine::EventManager::GetInstance()->AddListener(listenerClickEvent);
        }

        void Board::InitBoats()
        {
            m_Boats[0].SetName("Porte-Avion");
            m_Boats[0].SetSize(5);

            m_Boats[1].SetName("Croiseur");
            m_Boats[1].SetSize(4);

            m_Boats[2].SetName("Contre-Torpilleur");
            m_Boats[2].SetSize(3);

            m_Boats[3].SetName("Contre-Torpilleur");
            m_Boats[3].SetSize(3);

            m_Boats[4].SetName("Torpilleur");
            m_Boats[4].SetSize(2);
        }

        Board::~Board()
        {
            Engine::EventListener<Board, Engine::ClickEvent> listenerClickEvent(this, &Board::OnEvent);
            Engine::EventManager::GetInstance()->RemoveListener(listenerClickEvent);
        }

        void Board::Update(const sf::Vector2f& cursorPosition)
        {
            if (m_WasAttacked || !m_IsCurrent
                || cursorPosition.x < 0 || cursorPosition.x > BOARD_SIZE.x * TILE_SIZE.x
                || cursorPosition.y < 0 || cursorPosition.y > BOARD_SIZE.y * TILE_SIZE.y)
            {
                return;
            }

            if (GameManager::GetInstance()->IsPlacingBoats())
            {
                m_PlacedAllBoats = true;
                for (int i = 0; i < m_Boats.size(); i++)
                {
                    if (!m_Boats[i].IsPlaced())
                    {
                        m_SelectedBoatIndex = i;
                        m_PlacedAllBoats = false;
                        break;
                    }
                }
            }

            ManageTileSelection(cursorPosition);
        }

        void Board::ManageTileSelection(const sf::Vector2f &cursorPosition)
        {
            // Convert the cursor position to get the tile coordinates
            const float i = floorf(cursorPosition.x / static_cast<float>(TILE_SIZE.x));
            const float j = floorf(cursorPosition.y / static_cast<float>(TILE_SIZE.y));

            // Convert the coordinates to get the tile index on the board
            const size_t tileIndex = static_cast<size_t>(i) + static_cast<size_t>(j) * static_cast<size_t>(BOARD_SIZE.y);

            if (tileIndex > BOARD_SIZE.x * BOARD_SIZE.y)
            {
                LOG_WARNING("Tile index out of bound");
            }

            // If the tile is free
            if (m_SelectedTileIndex != tileIndex
                && (m_Board[tileIndex] == TileType::WATER || m_Board[tileIndex] == TileType::BOAT))
            {
                // Unselect previous selection
                UnselectTiles();

                // Select the new one
                SelectTiles(tileIndex);
            }
        }

        int Board::GetBoatTileOffsetIndex(const bool isBoatVertical, const int k, const int startIndex) const
        {
            int offsetSelectIndex;

            if (isBoatVertical)
            {
                offsetSelectIndex = startIndex + (k * BOARD_SIZE.x);
            }
            else
            {
                offsetSelectIndex = startIndex + k;
            }

            return offsetSelectIndex;
        }

        void Board::SelectTiles(const size_t tileIndex)
        {
            m_SelectedTileIndex = tileIndex;

            if (GameManager::GetInstance()->IsPlacingBoats())
            {
                const Boat& boat = m_Boats[m_SelectedBoatIndex];
                const bool isBoatVertical = boat.IsVertical();

                m_CanPlaceBoat = true;

                for (int k = 0; k < boat.GetSize(); k++)
                {
                    int tileIndex = GetBoatTileOffsetIndex(isBoatVertical, k, m_SelectedTileIndex);

                    CheckBoatPlacement(boat, tileIndex);
                    if (!m_CanPlaceBoat) break;

                    UpdateTileOnBoard(tileIndex, true);
                }
            }
            else
            {
                UpdateTileOnBoard(m_SelectedTileIndex, true);
            }
        }

        void Board::CheckBoatPlacement(const Boat &boat, const int tileIndex)
        {
            int lineNumber = m_SelectedTileIndex / BOARD_SIZE.y;

            if (m_Board[tileIndex] == TileType::BOAT)
            {
                m_CanPlaceBoat = false;
            }

            if (boat.IsVertical())
            {
                if (tileIndex >= BOARD_SIZE.x * BOARD_SIZE.y)
                {
                    m_CanPlaceBoat = false;
                }
            }
            else if (tileIndex >= (lineNumber + 1) * BOARD_SIZE.y)
            {
                m_CanPlaceBoat = false;
            }
        }

        void Board::UnselectTiles()
        {
            if (GameManager::GetInstance()->IsPlacingBoats())
            {
                const Boat& boat = m_Boats[m_SelectedBoatIndex];
                const bool isBoatVertical = boat.IsVertical();

                for (int k = 0; k < boat.GetSize(); k++)
                {
                    int tileIndex = GetBoatTileOffsetIndex(isBoatVertical, k, m_SelectedTileIndex);
                    UpdateTileOnBoard(tileIndex);
                }
            }
            else
            {
                UpdateTileOnBoard(m_SelectedTileIndex);
            }
        }

        void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // Draw the background map
            states.transform *= getTransform(); // Apply the transform
            states.texture = &m_TileSet; // Apply the tileset texture
            target.draw(m_Vertices, states); // Draw the vertex array

            // TODO : draw boats here
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
                    const size_t tileIndex = static_cast<size_t>(i) + static_cast<size_t>(j) * static_cast<size_t>(BOARD_SIZE.y);
                    int tileNumber = GetTileNumberFromType(tileIndex);

                    // Find its position in the tileset texture
                    int tu = tileNumber % (m_TileSet.getSize().x / TILE_SIZE.x);
                    int tv = tileNumber / (m_TileSet.getSize().x / TILE_SIZE.x);

                    // Get a pointer to the current tile's quad
                    CreateVertexQuad(i, j, tileIndex, tu, tv);
                }
            }
        }

        int Board::GetTileNumberFromType(const size_t tileIndex)
        {
            switch (m_Board[tileIndex])
            {
                case TileType::WATER:
                    return 1;

                case TileType::MISSED:
                    return 3;

                // TODO : Temporary representation (have a sprite in the Boat class)
                case TileType::BOAT:
                    return 4;

                case TileType::TOUCHED:
                    return 2;

                default:
                    return 4;
            }
        }

        void Board::CreateVertexQuad(unsigned int i, unsigned int j, const size_t tileIndex, int tu, int tv, const bool isSelected)
        {
            sf::Vertex* quad = &m_Vertices[tileIndex * 4];

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

            // Highlights selected tile
            if (isSelected)
            {
                quad[0].color = sf::Color::Yellow;
                quad[1].color = sf::Color::Yellow;
                quad[2].color = sf::Color::Yellow;
                quad[3].color = sf::Color::Yellow;
            }
            else
            {
                quad[0].color = sf::Color::White;
                quad[1].color = sf::Color::White;
                quad[2].color = sf::Color::White;
                quad[3].color = sf::Color::White;
            }
        }

        void Board::UpdateTileOnBoard(const int tileIndex, const bool isSelected)
        {
            // Retrieve the coordinates
            int i = tileIndex % BOARD_SIZE.y;
            int j = tileIndex / BOARD_SIZE.y;

            // Retrieve the tile number
            int tileNumber = GetTileNumberFromType(tileIndex);

            // Find its position in the tileset texture
            int tu = tileNumber % (m_TileSet.getSize().x / TILE_SIZE.x);
            int tv = tileNumber / (m_TileSet.getSize().x / TILE_SIZE.x);

            CreateVertexQuad(i, j, tileIndex, tu, tv, isSelected);
        }

        void Board::OnEvent(const Engine::Event* evnt)
        {
            if (m_IsCurrent && !m_WasAttacked)
            {
                if (const Engine::ClickEvent* clickEvent = dynamic_cast<const Engine::ClickEvent*>(evnt))
                {
                    if (clickEvent->IsRightClick())
                    {
                        if (GameManager::GetInstance()->IsPlacingBoats())
                        {
                            Boat& boat = m_Boats[m_SelectedBoatIndex];

                            UnselectTiles();
                            boat.Rotate();
                            SelectTiles(m_SelectedTileIndex);
                        }
                    }
                    else
                    {
                        const sf::Vector2f clickPosition = clickEvent->GetClickPosition();

                        // Check that click happened within the board limits
                        if (clickPosition.x < 0 || clickPosition.x > BOARD_SIZE.x * TILE_SIZE.x
                            || clickPosition.y < 0 || clickPosition.y > BOARD_SIZE.y * TILE_SIZE.y)
                        {
                            LOG_WARNING("Click outside of the board : ignored.");
                            return;
                        }

                        if (GameManager::GetInstance()->IsPlacingBoats())
                        {
                            if (m_CanPlaceBoat)
                            {
                                PlaceBoat();
                            }
                            else
                            {
                                LOG_WARNING("Can't place this boat here !");
                            }
                        }
                        else
                        {
                            HandleAttack();
                        }
                    }
                }
            }
        }

        void Board::PlaceBoat()
        {
            Boat& boat = m_Boats[m_SelectedBoatIndex];
            const bool isBoatVertical = boat.IsVertical();

            for (int k = 0; k < boat.GetSize(); k++)
            {
                int tileIndex = GetBoatTileOffsetIndex(isBoatVertical, k, m_SelectedTileIndex);
                m_Board[tileIndex] = TileType::BOAT;
                UpdateTileOnBoard(tileIndex);
            }

            boat.SetPositionIndex(m_SelectedTileIndex);
            LOG_DEBUG("Placed boat of type " << boat.GetName() << " at index " << boat.GetPositionIndex());

            boat.Place();
        }

        void Board::HandleAttack()
        {
            m_WasAttacked = true;

            // Attack in water
            if (m_Board[m_SelectedTileIndex] == TileType::WATER)
            {
                m_Board[m_SelectedTileIndex] = TileType::MISSED;
                LOG_INFO("You missed!");
            }
            // Attack on a boat
            else if (m_Board[m_SelectedTileIndex] == TileType::BOAT)
            {
                m_Board[m_SelectedTileIndex] = TileType::TOUCHED;

                // Retrieve the boat
                auto boat = std::find_if(m_Boats.begin(), m_Boats.end(), [&](const Boat& b)
                {
                    for (int k = 0; k < b.GetSize(); k++)
                    {
                        const int tileIndex = GetBoatTileOffsetIndex(b.IsVertical(), k, b.GetPositionIndex());

                        if (m_SelectedTileIndex == tileIndex)
                        {
                            return true;
                        }
                    }
                });

                // Mark it as touched
                boat->Touch();

                // Check if he's sunk
                if (boat->HasSunk())
                {
                    // TODO : Add score ?
                    LOG_INFO("You sunk a boat of type : " << boat->GetName());
                }
            }

            UpdateTileOnBoard(m_SelectedTileIndex);
        }
    }
}