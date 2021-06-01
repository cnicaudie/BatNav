//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#pragma once

namespace BatNav
{
    namespace Engine
    {
        enum class EventType
        {
            START_GAME	= 0,
            END_GAME	= 1,
            LEVEL		= 2,
            ACTION		= 3,
            CLICK		= 4
        };
    }
}