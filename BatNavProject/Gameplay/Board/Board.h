//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#pragma once

#include <vector>
#include <array>
#include "../../Engine/Event/EventTypes/Event.h"
#include "../Boats/Boat.h"

namespace BatNav
{
    namespace Gameplay
    {
        class Board : public sf::Drawable, public sf::Transformable
        {
        public:
            Board(const bool isCurrent, const bool displayBoats);
            ~Board();

            void Update(const sf::Vector2f& cursorPosition);

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            // Attack management
            void AttackRandom();
            void HandleAttack();
            inline bool WasAttacked() const { return m_WasAttacked && !m_SunkAllBoats; }
            inline void ResetAttack() { m_WasAttacked = false; }

            // Current board management
            inline void SetToCurrent() { m_IsCurrent = true; }
            inline void ResetCurrent() { m_IsCurrent = false; }

            // Boat management
            void PlaceBoat();
            void PlaceAllBoatsRandom(const bool autoConfirmation = false);
            inline bool PlacedAllBoats() const { return m_PlacedAllBoats && m_ConfirmedPlacement; }

        private:
            // Board loading/update
            void LoadBoard();
            void UpdateTileOnBoard(const int tileIndex, const bool isSelected = false);
            int GetTileNumberFromType(const size_t tileIndex);
            void CreateVertexQuad(unsigned int i, unsigned int j, const size_t tileIndex, int tu, int tv, const bool isSelected = false);

            // Tile selection
            void ManageTileSelection(const sf::Vector2f &cursorPosition);
            void SelectTiles(const size_t tileIndex);
            void UnselectTiles();

            // Boat management
            void InitBoats();
            void SelectBoatToPlace();
            void CheckBoatPlacement(const Boat &boat);
            void RotateBoat();
            void MoveBoat(Boat *boat);
            int GetBoatTileOffsetIndex(const bool isBoatVertical, const int k, const int startIndex) const;
            Boat* GetBoatFromTileIndex();

            // Events management
            void OnEvent(const Engine::Event* evnt);

            //====================//

            enum class TileType
            {
                WATER       = 0,
                MISSED      = 1,
                BOAT        = 2,
                TOUCHED     = 3
            };

            bool m_IsCurrent;
            bool m_WasAttacked;

            // Selection management
            int m_SelectedTileIndex;
            int m_SelectedBoatIndex;

            // Boat management
            bool m_DisplayBoats;
            bool m_CanPlaceBoat;
            bool m_PlacedAllBoats;
            bool m_SunkAllBoats;
            bool m_ConfirmedPlacement;
            int m_SunkBoats;
            std::array<Boat, 5> m_Boats;

            // Board representation
            std::vector<TileType> m_Board;
            sf::VertexArray m_Vertices;
            sf::Texture m_TileSet;
        };
    }
}


