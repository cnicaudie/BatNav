//
// Created by Charlotte Nicaudie on 09/06/2021.
//

#include "UIViewModel.h"

namespace BatNav
{
    namespace UI
    {
        UIViewModel* UIViewModel::m_UIViewModel = nullptr;

        UIViewModel* UIViewModel::GetInstance()
        {
            if (m_UIViewModel == nullptr)
            {
                m_UIViewModel = new UIViewModel();
            }

            return m_UIViewModel;
        }

        UIViewModel::UIViewModel() {}

        UIViewModel::~UIViewModel()
        {
            delete m_UIViewModel;
        }
    }
}