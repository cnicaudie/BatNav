//
// Created by Charlotte Nicaudie on 09/06/2021.
//

#pragma once

#include <SFML/System/Vector2.hpp>

namespace BatNav
{
    namespace Gameplay
    {
        class GameManager;
    }

    namespace UI
    {
        class UIViewModel
        {
        public:
            static UIViewModel* GetInstance();
            UIViewModel(const UIViewModel& uiViewModel) = delete;
            void operator=(const UIViewModel& uiViewModel) = delete;

            const int GetTurnTime() const { return m_TurnTime; }

        private:
            UIViewModel();
            ~UIViewModel();

            void SetTurnTime(const int turnTime) { m_TurnTime = turnTime; }

            //====================//

            static UIViewModel* m_UIViewModel; // Singleton instance

            int m_TurnTime;

            //====================//

            friend class Gameplay::GameManager;
        };
    }
}