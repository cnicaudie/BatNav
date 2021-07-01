//
// Created by Charlotte Nicaudie on 01/06/2021.
//

#include "InputManager.h"
#include "../Log/Log.h"
#include "../Event/EventManager.h"
#include "../Event/EventTypes/ClickEvent.h"

namespace BatNav
{
    namespace Engine
    {
        InputManager::InputManager()
            : m_IsClicking(false)
        {
        }

        void InputManager::ManageInputEvents(const sf::Event& event)
        {
            switch (event.type)
            {
                // === Keyboard
                /*
                case sf::Event::KeyPressed:
                {
                    break;
                }

                case sf::Event::KeyReleased:
                {
                    break;
                }
                */
                // === Mouse

                case sf::Event::MouseButtonPressed:
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        m_IsClicking = true;
                        m_MouseClickTimer.restart();
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        std::shared_ptr<ClickEvent> clickEvent = std::make_shared<ClickEvent>(m_MousePosition, true);
                        EventManager::GetInstance()->Fire(clickEvent);
                    }

                    break;
                }

                case sf::Event::MouseButtonReleased:
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        const float CLICK_THRESHOLD = 0.5f;
                        const float elapsedTime = m_MouseClickTimer.getElapsedTime().asSeconds();

                        //LOG_DEBUG("Click timer : " << elapsedTime << " sec");

                        if (m_IsClicking)
                        {
                            m_IsClicking = false;

                            if (elapsedTime < CLICK_THRESHOLD)
                            {
                                //LOG_DEBUG("Clicking at position : " << m_MousePosition.x << " / " << m_MousePosition.y);

                                // Fire a click event
                                std::shared_ptr<ClickEvent> clickEvent = std::make_shared<ClickEvent>(m_MousePosition, false);
                                EventManager::GetInstance()->Fire(clickEvent);
                            }
                            else
                            {
                                //LOG_DEBUG("Dropping");
                            }
                        }
                    }

                    break;
                }

                case sf::Event::MouseMoved:
                {
                    if (m_IsClicking)
                    {
                        //LOG_DEBUG("Dragging");
                    }

                    break;
                }

                default:
                    break;
            }
        }
    }
}