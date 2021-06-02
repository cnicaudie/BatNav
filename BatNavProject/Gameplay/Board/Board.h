//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../../Engine/Event/EventTypes/Event.h"

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
            void LoadBoard();

            inline bool WasAttacked() const { return m_WasAttacked; }
            inline bool IsCurrent() const { return m_IsCurrent; }
            inline void SetToCurrent() { m_IsCurrent = true; }
            inline void ResetCurrent()
            {
                m_IsCurrent = false;
            }
            inline void ResetAttack()
            {
                m_WasAttacked = false;
            }

        private:
            int GetTileNumberFromType(const size_t tileIndex);
            void CreateVertexQuad(unsigned int i, unsigned int j, const size_t tileIndex, int tu, int tv);

            void OnEvent(const Engine::Event* evnt);

            void SelectTile(const sf::Vector2f &cursorPosition);
            void UpdateSelectedTileOnBoard();

            //====================//

            enum class TileType
            {
                FREE        = 0,
                SELECTED    = 1,
                ATTACKED    = 2
            };

            int m_SelectedTileIndex;

            bool m_IsCurrent;
            bool m_WasAttacked;

            std::vector<TileType> m_Board;
            sf::VertexArray m_Vertices;

            sf::Texture m_TileSet;

        };
    }
}


