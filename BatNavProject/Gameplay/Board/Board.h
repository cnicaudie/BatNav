//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

namespace BatNav
{
    namespace Gameplay
    {
        class Board : public sf::Drawable, public sf::Transformable
        {
        public:
            Board();

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            void LoadBoard();

        private:
            std::vector<bool> m_Board;
            sf::VertexArray m_Vertices;
            sf::Texture m_TileSet;
        };
    }
}


