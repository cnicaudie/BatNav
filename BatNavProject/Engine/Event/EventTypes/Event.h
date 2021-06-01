//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#pragma once

#include "EventType.h"

namespace BatNav
{
    namespace Engine
    {
        class Event
        {
        public:
            Event(EventType eventType) : m_EventType(eventType) {};

            virtual bool operator==(const Event& other) const
            {
                return m_EventType == other.m_EventType;
            };

            inline const EventType GetEventType() const { return m_EventType; };

        private:
            EventType m_EventType;
        };
    }
}