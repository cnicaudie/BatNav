//
// Created by Charlotte Nicaudie on 09/06/2021.
//

#pragma once

#include <SFML/System/Vector2.hpp>

namespace BatNav
{
    namespace Gameplay
    {
        class Player;
    }

    namespace UI
    {
        class UIViewModel
        {
        public:
//            friend class Gameplay::Player;

            static UIViewModel* GetInstance();
            UIViewModel(const UIViewModel& uiViewModel) = delete;
            void operator=(const UIViewModel& uiViewModel) = delete;

        private:
            UIViewModel();
            ~UIViewModel();

            //====================//

            static UIViewModel* m_UIViewModel; // Singleton instance

        };
    }
}