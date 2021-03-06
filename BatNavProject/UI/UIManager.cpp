//
// Created by Charlotte Nicaudie on 09/06/2021.
//

#include "UIManager.h"
#include "UIViewModel.h"
#include "../Engine/Event/EventManager.h"
#include "../Engine/Log/Log.h"
#include "../Gameplay/Events/BoardEvent.h"
#include "../Gameplay/GameManager.h"

namespace BatNav
{
    namespace UI
    {
        static const sf::Vector2f BUTTON_SIZE{ 150.f, 50.f };

        UIManager::UIManager(sf::RenderWindow* window)
                : m_Window(window)
                , m_ToggleMainMenu(true)
                , m_StartButton(BUTTON_SIZE)
                , m_CloseButton(BUTTON_SIZE)
                , m_ConfirmButton(BUTTON_SIZE)
                , m_RandomButton(BUTTON_SIZE)
        {
            const sf::Vector2f WINDOW_CENTER{ window->getView().getCenter() };

            m_MainFont.loadFromFile("../Assets/Avenir.ttc");

            InitTexts(WINDOW_CENTER);
            InitButtons(WINDOW_CENTER);

            // Configure EventListeners
            //Engine::EventListener<UIManager, Engine::Event> listenerGameOver(this, &UIManager::OnEvent);
            //Engine::EventManager::GetInstance()->AddListener(listenerGameOver);
        }

        void UIManager::InitTexts(const sf::Vector2f& WINDOW_CENTER)
        {
            const float TEXT_OFFSET = 150.f;

            // === In Game UI
            m_TurnTimeText.setFont(m_MainFont);
            m_TurnTimeText.setCharacterSize(30);
            m_TurnTimeText.setFillColor(sf::Color::White);
            m_TurnTimeText.setString("0");
            m_TurnTimeText.setStyle(sf::Text::Bold);
            m_TurnTimeText.setPosition(WINDOW_CENTER.x - TEXT_OFFSET - (m_TurnTimeText.getGlobalBounds().width / 2), WINDOW_CENTER.y - TEXT_OFFSET / 3);

            // === Main Menu
            /*m_MainTitle.setFont(m_MainFont);
            m_MainTitle.setCharacterSize(80);
            m_MainTitle.setFillColor(sf::Color::White);
            m_MainTitle.setString("BATNAV");
            m_MainTitle.setStyle(sf::Text::Bold);
            m_MainTitle.setPosition(WINDOW_CENTER.x - (m_MainTitle.getGlobalBounds().width / 2), WINDOW_CENTER.y * 0.15f);
            */

            // === End Level/Game Menu

            m_EndGameText.setFont(m_MainFont);
            m_EndGameText.setCharacterSize(50);
            m_EndGameText.setFillColor(sf::Color::White);
            m_EndGameText.setString("GAME OVER");
            m_EndGameText.setStyle(sf::Text::Bold);
            m_EndGameText.setPosition(WINDOW_CENTER.x - TEXT_OFFSET - (m_EndGameText.getGlobalBounds().width / 2), WINDOW_CENTER.y -  2 * TEXT_OFFSET);
        }

        void UIManager::InitButtons(const sf::Vector2f& WINDOW_CENTER)
        {
            const float MAIN_MENU_BUTTONS_OFFSET = 100.f;
            const float IN_GAME_BUTTONS_OFFSET = 100.f;

            // === Main Menu

            const sf::Vector2f startButtonPosition{ WINDOW_CENTER.x - 3 * MAIN_MENU_BUTTONS_OFFSET, WINDOW_CENTER.y - 2 * MAIN_MENU_BUTTONS_OFFSET };
            m_StartButton.SetButtonPosition(startButtonPosition);
            m_StartButton.SetButtonTextFont(m_MainFont);
            m_StartButton.SetButtonTextString("Start");
            m_StartButton.SetButtonTextPosition(startButtonPosition);

            const sf::Vector2f closeButtonPosition{ WINDOW_CENTER.x - 3 * MAIN_MENU_BUTTONS_OFFSET, WINDOW_CENTER.y - MAIN_MENU_BUTTONS_OFFSET };
            m_CloseButton.SetButtonPosition(closeButtonPosition);
            m_CloseButton.SetButtonTextFont(m_MainFont);
            m_CloseButton.SetButtonTextString("Quit");
            m_CloseButton.SetButtonTextPosition(closeButtonPosition);

            // === Boat Placement Menu

            const sf::Vector2f randomButtonPosition{ WINDOW_CENTER.x - IN_GAME_BUTTONS_OFFSET - 50.f, WINDOW_CENTER.y - 2 * IN_GAME_BUTTONS_OFFSET};
            m_RandomButton.SetButtonPosition(randomButtonPosition);
            m_RandomButton.SetButtonTextFont(m_MainFont);
            m_RandomButton.SetButtonTextString("Random");
            m_RandomButton.SetButtonTextPosition(randomButtonPosition);

            const sf::Vector2f confirmButtonPosition{ WINDOW_CENTER.x - IN_GAME_BUTTONS_OFFSET - 50.f, WINDOW_CENTER.y - IN_GAME_BUTTONS_OFFSET };
            m_ConfirmButton.SetButtonPosition(confirmButtonPosition);
            m_ConfirmButton.SetButtonTextFont(m_MainFont);
            m_ConfirmButton.SetButtonTextString("Confirm");
            m_ConfirmButton.SetButtonTextPosition(confirmButtonPosition);
        }

        UIManager::~UIManager()
        {
            // Remove listeners
            //Engine::EventListener<UIManager, Engine::Event> listenerGameOver(this, &UIManager::OnEvent);
            //Engine::EventManager::GetInstance()->RemoveListener(listenerGameOver);
        }

        void UIManager::Update(float deltaTime)
        {
            UpdateTexts();
            ManageButtons();
        }

        void UIManager::UpdateTexts()
        {
            // TODO : Score ?

            m_TurnTimeText.setString(std::to_string(UIViewModel::GetInstance()->GetTurnTime()));
        }

        void UIManager::ManageButtons()
        {
            if (m_ToggleMainMenu)
            {
                if (m_StartButton.WasClicked())
                {
                    LOG_INFO("Starting game...");
                    m_StartButton.ResetClickStatus();
                    m_ToggleMainMenu = false;

                    std::shared_ptr<Engine::Event> evnt = std::make_shared<Engine::Event>(Engine::EventType::START_GAME);
                    Engine::EventManager::GetInstance()->Fire(evnt);
                }
                else if (m_CloseButton.WasClicked())
                {
                    LOG_INFO("Bye !");
                    m_Window->close();
                }
            }
            else if (m_ConfirmButton.WasClicked())
            {
                m_ConfirmButton.ResetClickStatus();

                std::shared_ptr<Gameplay::BoardEvent> evnt = std::make_shared<Gameplay::BoardEvent>(Gameplay::BoardStatus::BOAT_PLACEMENT_CONFIRM);
                Engine::EventManager::GetInstance()->Fire(evnt);
            }
            else if (m_RandomButton.WasClicked())
            {
                m_RandomButton.ResetClickStatus();

                std::shared_ptr<Gameplay::BoardEvent> evnt = std::make_shared<Gameplay::BoardEvent>(Gameplay::BoardStatus::BOAT_PLACEMENT_RANDOM);
                Engine::EventManager::GetInstance()->Fire(evnt);
            }
        }

        void UIManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if (m_ToggleMainMenu)
            {
                //target.draw(m_MainTitle);
                target.draw(m_StartButton);
                target.draw(m_CloseButton);
            }
            else
            {
                if (Gameplay::GameManager::GetInstance()->IsPlacingBoats())
                {
                    target.draw(m_ConfirmButton);
                    target.draw(m_RandomButton);
                }
                else if (Gameplay::GameManager::GetInstance()->IsGameOver())
                {
                    target.draw(m_EndGameText);
                }
                else
                {
                    target.draw(m_TurnTimeText);
                }
            }
        }

        void UIManager::OnEvent(const Engine::Event* evnt)
        {
            // TODO
        }
    }
}