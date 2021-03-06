//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#include <cmath>
#include "Board.h"
#include "../GameManager.h"
#include "../../Engine/Event/EventTypes/ClickEvent.h"
#include "../../Engine/Maths/Maths.h"
#include "../Events/BoardEvent.h"

namespace BatNav
{
    namespace Gameplay
    {
        static const sf::Vector2u BOARD_SIZE { 10, 10 };
        static const sf::Vector2u TILE_SIZE { 32, 32 };

        Board::Board(const bool isCurrent, const bool displayBoats)
            : m_Board(BOARD_SIZE.x * BOARD_SIZE.y, TileType::WATER)
            , m_Boats()
            , m_IsCurrent(isCurrent)
            , m_WasAttacked(false)
            , m_DisplayBoats(displayBoats)
            , m_CanPlaceBoat(false)
            , m_PlacedAllBoats(false)
            , m_SunkAllBoats(false)
            , m_ConfirmedPlacement(false)
            , m_SunkBoats(0)
            , m_SelectedBoatIndex(0)
            , m_SelectedTileIndex(0)
        {
            // Board loading
            if (!m_TileSet.loadFromFile("../Assets/batnav_sheet.png"))
            {
                LOG_ERROR("TileSet was not loaded correctly !");
            }

            LoadBoard();

            // Boats preparation
            InitBoats();

            // Event listeners configuration
            Engine::EventListener<Board, Engine::ClickEvent> listenerClickEvent(this, &Board::OnEvent);
            Engine::EventListener<Board, BoardEvent> listenerBoardEvent(this, &Board::OnEvent);
            Engine::EventManager::GetInstance()->AddListener(listenerClickEvent);
            Engine::EventManager::GetInstance()->AddListener(listenerBoardEvent);

            LOG_INFO("Created Board");
        }

        Board::~Board()
        {
            Engine::EventListener<Board, Engine::ClickEvent> listenerClickEvent(this, &Board::OnEvent);
            Engine::EventListener<Board, BoardEvent> listenerBoardEvent(this, &Board::OnEvent);
            Engine::EventManager::GetInstance()->RemoveListener(listenerClickEvent);
            Engine::EventManager::GetInstance()->RemoveListener(listenerBoardEvent);

            LOG_INFO("Destroyed Board");
        }

        void Board::Update(const sf::Vector2f& cursorPosition)
        {
            if (m_SunkAllBoats)
            {
                LOG_INFO("All boats were sunk !");

                std::shared_ptr<Engine::Event> evnt = std::make_shared<Engine::Event>(Engine::EventType::END_GAME);
                Engine::EventManager::GetInstance()->Fire(evnt);

                m_SunkAllBoats = false;
                return;
            }

            if (m_WasAttacked || !m_IsCurrent) return;

            if (GameManager::GetInstance()->IsPlacingBoats())
            {
                if (!m_PlacedAllBoats)
                {
                    SelectBoatToPlace();
                }
            }

            if (cursorPosition.x > 0.f && cursorPosition.x < static_cast<float>(BOARD_SIZE.x * TILE_SIZE.x)
                    && cursorPosition.y > 0.f && cursorPosition.y < static_cast<float>(BOARD_SIZE.y * TILE_SIZE.y))
            {
                    ManageTileSelection(cursorPosition);
            }
        }

        void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // Draw boats
            for (auto boat : m_Boats)
            {
                target.draw(boat);
            }

            // Draw the board
            states.transform *= getTransform(); // Apply the transform
            states.texture = &m_TileSet; // Apply the tileset texture
            target.draw(m_Vertices, states); // Draw the vertex array
        }

        // ========== BOARD LOADING / UPDATE

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
                    int tu = tileNumber % static_cast<int>(m_TileSet.getSize().x / TILE_SIZE.x);
                    int tv = tileNumber / static_cast<int>(m_TileSet.getSize().x / TILE_SIZE.x);

                    // Get a pointer to the current tile's quad
                    CreateVertexQuad(i, j, tileIndex, tu, tv);
                }
            }
        }

        void Board::UpdateTileOnBoard(const int tileIndex, const bool isSelected)
        {
            // Retrieve the coordinates
            int i = tileIndex % static_cast<int>(BOARD_SIZE.x);
            int j = tileIndex / static_cast<int>(BOARD_SIZE.y);

            // Retrieve the tile number
            int tileNumber = GetTileNumberFromType(tileIndex);

            // Find its position in the tileset texture
            int tu = tileNumber % static_cast<int>(m_TileSet.getSize().x / TILE_SIZE.x);
            int tv = tileNumber / static_cast<int>(m_TileSet.getSize().x / TILE_SIZE.x);

            CreateVertexQuad(i, j, tileIndex, tu, tv, isSelected);
        }

        int Board::GetTileNumberFromType(const size_t tileIndex)
        {
            switch (m_Board[tileIndex])
            {
                case TileType::WATER:
                    return 0;

                case TileType::MISSED:
                    return 1;

                case TileType::BOAT:
                    return m_DisplayBoats ? 3 : 0;

                case TileType::TOUCHED:
                    return 2;

                default:
                    return 3;
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

        // ========== TILE SELECTION

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

            if (m_Board[tileIndex] == TileType::WATER || m_Board[tileIndex] == TileType::BOAT)
            {
                // Unselect previous selection
                UnselectTiles();

                // Select the new one
                SelectTiles(tileIndex);
            }
        }

        void Board::SelectTiles(const size_t tileIndex)
        {
            m_SelectedTileIndex = tileIndex;

            if (GameManager::GetInstance()->IsPlacingBoats() && !m_PlacedAllBoats)
            {
                const Boat& boat = m_Boats[m_SelectedBoatIndex];

                CheckBoatPlacement(boat);

                if (m_CanPlaceBoat)
                {
                    for (int k = 0; k < boat.GetSize(); k++)
                    {
                        int boatTileOffsetIndex = GetBoatTileOffsetIndex(boat.IsVertical(), k, m_SelectedTileIndex);

                        UpdateTileOnBoard(boatTileOffsetIndex, true);
                    }
                }
            }
            else
            {
                UpdateTileOnBoard(m_SelectedTileIndex, true);
            }
        }

        void Board::UnselectTiles()
        {
            if (GameManager::GetInstance()->IsPlacingBoats() && !m_PlacedAllBoats)
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

        // ========== BOAT MANAGEMENT

        void Board::InitBoats()
        {
            m_Boats[0].SetName("Porte-Avion");
            m_Boats[0].SetSize(5);
            m_Boats[0].InitSprite(TILE_SIZE);

            m_Boats[1].SetName("Croiseur");
            m_Boats[1].SetSize(4);
            m_Boats[1].InitSprite(TILE_SIZE);

            m_Boats[2].SetName("Contre-Torpilleur");
            m_Boats[2].SetSize(3);
            m_Boats[2].InitSprite(TILE_SIZE);

            m_Boats[3].SetName("Contre-Torpilleur");
            m_Boats[3].SetSize(3);
            m_Boats[3].InitSprite(TILE_SIZE);

            m_Boats[4].SetName("Torpilleur");
            m_Boats[4].SetSize(2);
            m_Boats[4].InitSprite(TILE_SIZE);
        }

        void Board::SelectBoatToPlace()
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

            if (m_PlacedAllBoats) m_CanPlaceBoat = false;
        }

        void Board::CheckBoatPlacement(const Boat &boat)
        {
            m_CanPlaceBoat = true;

            for (int k = 0; k < boat.GetSize(); k++)
            {
                const int lineNumber = m_SelectedTileIndex / static_cast<int>(BOARD_SIZE.y);
                const int boatTileOffsetIndex = GetBoatTileOffsetIndex(boat.IsVertical(), k, m_SelectedTileIndex);

                if (m_Board[boatTileOffsetIndex] == TileType::BOAT
                || (boat.IsVertical() && boatTileOffsetIndex >= BOARD_SIZE.x * BOARD_SIZE.y)
                || (!boat.IsVertical() && boatTileOffsetIndex >= (lineNumber + 1) * BOARD_SIZE.y))
                {
                    m_CanPlaceBoat = false;
                    return;
                }
            }
        }

        void Board::PlaceBoat()
        {
            if (m_CanPlaceBoat && !m_PlacedAllBoats)
            {
                UnselectTiles();

                Boat& boat = m_Boats[m_SelectedBoatIndex];

                for (int k = 0; k < boat.GetSize(); k++)
                {
                    int tileIndex = GetBoatTileOffsetIndex(boat.IsVertical(), k, m_SelectedTileIndex);
                    m_Board[tileIndex] = TileType::BOAT;
                    UpdateTileOnBoard(tileIndex);
                }

                boat.SetPosition({
                static_cast<float>((m_SelectedTileIndex % BOARD_SIZE.x) * TILE_SIZE.x),
                static_cast<float>((m_SelectedTileIndex / BOARD_SIZE.y) * TILE_SIZE.y),
                });
                boat.SetPositionIndex(m_SelectedTileIndex);
                boat.Place();
            }
        }

        void Board::RotateBoat()
        {
            UnselectTiles();
            m_Boats[m_SelectedBoatIndex].Rotate();
            SelectTiles(m_SelectedTileIndex);
        }

        void Board::MoveBoat(Boat *boat)
        {
            if (m_PlacedAllBoats) m_PlacedAllBoats = false;

            LOG_INFO("Moving boat...");

            // Remove boat from board
            int boatIndexOnBoard = boat->GetPositionIndex();

            for (int k = 0; k < boat->GetSize(); k++)
            {
                int tileIndex = GetBoatTileOffsetIndex(boat->IsVertical(), k, boatIndexOnBoard);
                m_Board[tileIndex] = TileType::WATER;
                UpdateTileOnBoard(tileIndex);
            }

            boat->Unplace();

            // Select it for placement
            m_SelectedBoatIndex = static_cast<int>(boat - m_Boats.begin());
        }

        void Board::PlaceAllBoatsRandom(const bool autoConfirmation)
        {
            LOG_INFO("Random boat placement...");

            UnselectTiles();

            for (int i = 0; i < m_Boats.size(); i++)
            {
                if (!m_Boats[i].IsPlaced())
                {
                    m_SelectedBoatIndex = i;

                    Boat& boat = m_Boats[m_SelectedBoatIndex];
                    float xPosition, yPosition;

                    // Find a valid position randomly
                    do
                    {
                        if (Engine::Maths::GetRandomBool()) boat.Rotate();

                        if (boat.IsVertical())
                        {
                            xPosition = Engine::Maths::GetRandomFloat(0.f, static_cast<float>(BOARD_SIZE.x));
                            yPosition = Engine::Maths::GetRandomFloat(0.f, static_cast<float>(BOARD_SIZE.y - boat.GetSize()));
                        }
                        else
                        {
                            xPosition = Engine::Maths::GetRandomFloat(0.f, static_cast<float>(BOARD_SIZE.x - boat.GetSize()));
                            yPosition = Engine::Maths::GetRandomFloat(0.f, static_cast<float>(BOARD_SIZE.y));
                        }

                        m_SelectedTileIndex = static_cast<int>(xPosition * yPosition);

                        CheckBoatPlacement(boat);

                    } while (!m_CanPlaceBoat);

                    // Place the boat
                    PlaceBoat();
                }
            }

            m_PlacedAllBoats = true;
            m_CanPlaceBoat = false;

            if (autoConfirmation) m_ConfirmedPlacement = true;
        }

        int Board::GetBoatTileOffsetIndex(const bool isBoatVertical, const int k, const int startIndex) const
        {
            int offsetSelectIndex;

            if (isBoatVertical)
            {
                offsetSelectIndex = startIndex + static_cast<int>(k * BOARD_SIZE.x);
            }
            else
            {
                offsetSelectIndex = startIndex + k;
            }

            return offsetSelectIndex;
        }

        Boat* Board::GetBoatFromTileIndex()
        {
            return std::find_if(m_Boats.begin(), m_Boats.end(), [&](const Boat& b)
            {
                for (int k = 0; k < b.GetSize(); k++)
                {
                    const int tileIndex = GetBoatTileOffsetIndex(b.IsVertical(), k, b.GetPositionIndex());

                    if (m_SelectedTileIndex == tileIndex)
                    {
                        return true;
                    }
                }

                return false;
            });
        }

        // ========== ATTACKS MANAGEMENT

        void Board::AttackRandom()
        {
            UnselectTiles();

            do
            {
                m_SelectedTileIndex = static_cast<int>(Engine::Maths::GetRandomFloat
                        (
                                0.f, static_cast<float>(BOARD_SIZE.x * BOARD_SIZE.y)
                        ));

                HandleAttack();
            }
            while (!m_WasAttacked);
        }

        void Board::HandleAttack()
        {
            if (!m_WasAttacked)
            {
                if (m_Board[m_SelectedTileIndex] == TileType::TOUCHED
                    || m_Board[m_SelectedTileIndex] == TileType::MISSED)
                {
                    LOG_WARNING("Can't attack a already attacked tile");
                }
                else
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
                        Boat* boat = GetBoatFromTileIndex();

                        // Mark it as touched
                        boat->Touch();

                        // Check if he's sunk
                        if (boat->HasSunk())
                        {
                            // TODO : Add score ?
                            LOG_INFO("You sunk a boat of type : " << boat->GetName());

                            m_SunkBoats += 1;

                            if (m_SunkBoats == m_Boats.size())
                            {
                                m_SunkAllBoats = true;
                            }
                        }
                    }

                    UpdateTileOnBoard(m_SelectedTileIndex);
                }
            }
        }

        // ========== EVENTS MANAGEMENT

        void Board::OnEvent(const Engine::Event* evnt)
        {
            if (!m_IsCurrent) return;

            const auto* boardEvent = dynamic_cast<const BoardEvent*>(evnt);
            const auto* clickEvent = dynamic_cast<const Engine::ClickEvent*>(evnt);

            if (GameManager::GetInstance()->IsPlacingBoats() && boardEvent != nullptr)
            {
                switch (boardEvent->GetBoardStatus())
                {
                    case BoardStatus::BOAT_PLACEMENT_RANDOM:
                    {
                        if (!m_PlacedAllBoats)
                        {
                            PlaceAllBoatsRandom();
                        }
                        else
                        {
                            // TODO : Clear board and replace randomly ?
                            LOG_WARNING("All boats were placed !");
                        }
                        break;
                    }

                    case BoardStatus::BOAT_PLACEMENT_CONFIRM:
                    {
                        if (m_PlacedAllBoats)
                        {
                            UnselectTiles();
                            m_ConfirmedPlacement = true;
                        }
                        else
                        {
                            LOG_WARNING("Please place all boats before confirming placement.");
                        }
                        break;
                    }

                    default:
                        LOG_WARNING("Unexpected event.");
                        break;
                }
            }
            else if (clickEvent != nullptr && GameManager::GetInstance()->IsPlacingBoats())
            {
                const sf::Vector2f clickPosition = clickEvent->GetClickPosition();

                if (clickPosition.x < 0.f || clickPosition.x > static_cast<float>(BOARD_SIZE.x * TILE_SIZE.x)
                    || clickPosition.y < 0.f || clickPosition.y > static_cast<float>(BOARD_SIZE.y * TILE_SIZE.y))
                {
                    return;
                }

                if (clickEvent->IsRightClick())
                {
                    if (!m_PlacedAllBoats)
                    {
                        RotateBoat();
                    }
                }
                else
                {
                    if (!m_CanPlaceBoat)
                    {
                        Boat* boat = GetBoatFromTileIndex();

                        if (boat != m_Boats.end())
                        {
                            MoveBoat(boat);
                        }
                        else if (m_PlacedAllBoats)
                        {
                            LOG_WARNING("All boats were placed !");
                        }
                        else
                        {
                            LOG_WARNING("Can't place this boat here !");
                        }
                    }
                }
            }
        }
    }
}