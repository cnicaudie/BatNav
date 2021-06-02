//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#pragma once

#include <vector>
#include "../GameplayIncludes.h"
#include "../../Engine/Event/EventTypes/Event.h"
#include "../Boats/Boat.h"

namespace BatNav
{
    namespace Gameplay
    {
        class Board : public sf::Drawable, public sf::Transformable
        {
        public:
            Board(const bool isCurrent);
            ~Board();

            void Update(const sf::Vector2f& cursorPosition);
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            inline bool IsCurrent() const { return m_IsCurrent; }
            inline bool WasAttacked() const { return m_WasAttacked; }
            inline bool PlacedAllBoats() const { return m_PlacedAllBoats; }
            inline void SetToCurrent() { m_IsCurrent = true; }
            inline void ResetCurrent() { m_IsCurrent = false; }
            inline void ResetAttack() { m_WasAttacked = false; }

        private:
            void InitBoats();
            void LoadBoard();
            void UpdateTileOnBoard(const int tileIndex, const bool isSelected = false);

            int GetTileNumberFromType(const size_t tileIndex);
            void CreateVertexQuad(unsigned int i, unsigned int j, const size_t tileIndex, int tu, int tv, const bool isSelected = false);

            void ManageTileSelection(const sf::Vector2f &cursorPosition);
            int GetBoatTileOffsetIndex(const bool isBoatVertical, int k, int startIndex) const;
            void SelectTiles(const size_t tileIndex);
            void UnselectTiles();

            void OnEvent(const Engine::Event* evnt);
            void PlaceBoat();
            void HandleAttack();

            //====================//

            enum class TileType
            {
                WATER       = 0,
                MISSED      = 1,
                BOAT        = 2,
                TOUCHED     = 3
            };

            int m_SelectedTileIndex;
            int m_SelectedBoatIndex;

            bool m_IsCurrent;
            bool m_WasAttacked;
            bool m_PlacedAllBoats;

            std::vector<Boat> m_Boats;

            // Board representation
            std::vector<TileType> m_Board;
            sf::VertexArray m_Vertices;
            sf::Texture m_TileSet;
        };
    }
}


