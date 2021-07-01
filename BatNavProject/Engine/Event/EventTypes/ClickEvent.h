//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Event.h"

namespace BatNav
{
    namespace Engine
    {
        class ClickEvent : public Event
        {
        public:
            ClickEvent(const sf::Vector2f& clickPosition, const bool isRightClick = false)
            : Event(EventType::CLICK), m_ClickPosition(clickPosition), m_IsRightClick(isRightClick) {};

            virtual bool operator==(const Event& other) const override
            {
                if (const ClickEvent* otherClickEvent = dynamic_cast<const ClickEvent*>(&other))
                {
                    return m_ClickPosition == otherClickEvent->m_ClickPosition;
                }

                return false;
            };

            inline const sf::Vector2f GetClickPosition() const { return m_ClickPosition; };
            inline const bool IsRightClick() const { return m_IsRightClick; };

        private:
            sf::Vector2f m_ClickPosition;
            bool m_IsRightClick;
        };
    }
}