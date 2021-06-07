//
// Created by Charlotte Nicaudie on 07/06/2021.
//

#include <SFML/System/Vector2.hpp>
#include <random>

namespace BatNav
{
    namespace Engine
    {
        namespace Maths
        {
            static const float GetRandomFloat(const float minValue, const float maxValue)
            {
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_real_distribution<float> dist(minValue, maxValue);
                return dist(mt);
            }

            static const bool GetRandomBool()
            {
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_int_distribution<bool> dist(0, 1);
                return dist(mt);
            }
        }
    }
}