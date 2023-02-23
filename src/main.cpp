#include <iostream>
#include "Game.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello CMake." << std::endl;

    const int FPS = 120;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    int frameCount = 0;

    // Init SDL2 and its components
    if (!Game::getInstance().Initialize())
    {
        return 1;
    }


    // Main game loop
    while (Game::getInstance().IsRunning())
    {

        // Init FPS
        frameStart = SDL_GetTicks();

        // Update
        Game::getInstance().Update();

        // Draw
        Game::getInstance().Draw();

        // Cap FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }

        frameCount++;
    }

    Game::getInstance().Clean();

    return 0;
}
