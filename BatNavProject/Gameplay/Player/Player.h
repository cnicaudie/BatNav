//
// Created by Charlotte Nicaudie on 11/06/2021.
//

#pragma once

#include "../Board/Board.h"

namespace BatNav
{
    namespace Gameplay
    {
        class Player
        {
        public:
            Player(const bool isRandom, const bool isCurrent, const bool displayBoats);

            //void Update();

            void PlaceBoat();
            void Attack(Board& board);

            inline const bool IsRandom() const { return m_IsRandom; }
            inline Board& GetBoard() { return m_Board; }

        private:
            bool m_IsRandom;
            int m_Score;
            Board m_Board;
        };
    }
}