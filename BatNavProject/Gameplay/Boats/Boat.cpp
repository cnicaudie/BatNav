//
// Created by Charlotte Nicaudie on 02/06/2021.
//

#include "Boat.h"
#include <cmath>

namespace BatNav
{
    namespace Gameplay
    {
        Boat::Boat()
            : m_Position{ 0.f, 0.f }
            , m_Name("")
            , m_Size(0)
            , m_TouchedCount(0)
            , m_PositionIndex(0)
            , m_Angle(0.f)
            , m_IsVertical(true)
            , m_IsPlaced(false)
            , m_HasSunk(false)
        {}

        void Boat::InitSprite(const sf::Vector2u& tileSize)
        {
            if (!m_Texture.loadFromFile("../Assets/" + m_Name + ".png"))
            {
                LOG_ERROR("Boat texture was not loaded correctly !");
            }

            m_Sprite.setTexture(m_Texture);
        }

        void Boat::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if (m_IsPlaced)
            {
                target.draw(m_Sprite);
            }
        }

        void Boat::Touch()
        {
            LOG_INFO("Touched!");
            ++m_TouchedCount;

            if (m_TouchedCount == m_Size)
            {
                LOG_INFO("Sunken!");
                m_HasSunk = true;
            }
        }

        void Boat::Rotate()
        {
            m_Angle = std::fmod((m_Angle - 90), -360.f);
            m_Sprite.setRotation(m_Angle);
            m_IsVertical = !m_IsVertical;
        }

        void Boat::SetPosition(const sf::Vector2f position)
        {
            sf::FloatRect spriteBounds = m_Sprite.getGlobalBounds();
            m_Position = position;

            if (m_Angle == -90)
            {
                m_Position.y += spriteBounds.height;
            }
            else if (m_Angle == -180)
            {
                m_Position.x += spriteBounds.width;
                m_Position.y += spriteBounds.height;
            }
            else if (m_Angle == -270)
            {
                m_Position.x += spriteBounds.width;
            }

            m_Sprite.setPosition(m_Position);
        }
    }
}