//
// Created by Charlotte Nicaudie on 02/06/2021.
//

#include "Boat.h"

namespace BatNav
{
    namespace Gameplay
    {
        Boat::Boat()
            : m_Name("")
            , m_Size(0)
            , m_TouchedCount(0)
            , m_PositionIndex(0)
            , m_IsVertical(true)
            , m_IsPlaced(false)
            , m_HasSunk(false)
        {}

        void Boat::Touch()
        {
            LOG_INFO("Touched!");
            ++m_TouchedCount;

            if (m_TouchedCount == m_Size)
            {
                LOG_INFO("Sunken!");
                m_HasSunk = true;
            }
        }
    }
}