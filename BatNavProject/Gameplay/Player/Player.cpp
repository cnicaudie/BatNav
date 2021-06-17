//
// Created by Charlotte Nicaudie on 15/06/2021.
//

#include "Player.h"

namespace BatNav
{
    namespace Gameplay
    {
        Player::Player(const bool isRandom, const bool isCurrent, const bool displayBoats)
            : m_IsRandom(isRandom), m_Score(0), m_Board(isCurrent, displayBoats)
        {}

        void Player::PlaceBoat()
        {
            if (!m_IsRandom)
            {
                m_Board.PlaceBoat();
            }
        }

        void Player::Attack(Board &board)
        {
            if (!m_IsRandom)
            {
                board.HandleAttack();
            }
        }
    }
}