//
// Created by Charlotte Nicaudie on 02/06/2021.
//

#pragma once

#include <string>
#include "../GameplayIncludes.h"

namespace BatNav
{
    namespace Gameplay
    {
        class Boat
        {
        public:
            Boat();

            inline void Place()
            {
                LOG_INFO("Placed boat : " << m_Name);
                m_IsPlaced = true;
            }
            inline void Unplace() { m_IsPlaced = false; }

            void Touch();

            inline void SetName(const std::string& name) { m_Name = name; }
            inline void SetSize(const int size) { m_Size = size; }
            inline void SetPositionIndex(const int index) { m_PositionIndex = index; }
            inline void Rotate() { m_IsVertical = !m_IsVertical; }

            inline const std::string GetName() const { return m_Name; }
            inline const int GetSize() const { return m_Size; }
            inline const int GetPositionIndex() const { return m_PositionIndex; }

            inline const bool IsVertical() const { return m_IsVertical; }
            inline const bool IsPlaced() const { return m_IsPlaced; }
            inline const bool HasSunk() const { return m_HasSunk; }

        private:
            std::string m_Name;
            int m_Size;
            int m_TouchedCount;
            int m_PositionIndex;
            bool m_IsVertical;
            bool m_IsPlaced;
            bool m_HasSunk;
        };
    }
}


