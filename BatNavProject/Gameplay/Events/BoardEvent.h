//
// Created by Charlotte Nicaudie on 09/06/2021.
//

#pragma once

#include "../../Engine/Event/EventTypes/Event.h"
#include "../Board/BoardStatus.h"

namespace BatNav
{
    namespace Gameplay
    {
        class BoardEvent : public Engine::Event
        {
        public:
            BoardEvent(const BoardStatus boardStatus)
                    : Event(Engine::EventType::GAME), m_BoardStatus(boardStatus) {};

            virtual bool operator==(const Event& other) const override
            {
                if (const BoardEvent* otherBoatEvent = dynamic_cast<const BoardEvent*>(&other))
                {
                    return m_BoardStatus == otherBoatEvent->m_BoardStatus;
                }

                return false;
            };

            const BoardStatus GetBoardStatus() const { return m_BoardStatus; }

        private:
            BoardStatus m_BoardStatus;
        };
    }
}


