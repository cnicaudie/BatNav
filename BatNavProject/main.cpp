#include <SFML/Graphics.hpp>
#include "Gameplay/GameManager.h"

int main()
{
    BatNav::Gameplay::GameManager* game = BatNav::Gameplay::GameManager::GetInstance();
    game->RunGameLoop();

    return EXIT_SUCCESS;
}