//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#pragma once

namespace BatNav
{
    namespace Engine
    {
        class Event;

        class IEventListener
        {
        public:
            virtual bool operator==(IEventListener* other) const = 0;
            virtual void Fire(Event* evnt) const = 0;
        };
    }
}