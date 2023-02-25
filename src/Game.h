//
// Created by yot on 23/02/23.
//

#ifndef FLAPPYBIRD_GAME_H
#define FLAPPYBIRD_GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>
#include "InputHandler.h"
#include "TTFManager.h"
#include "ConfigHelper.h"
#include "Bird.h"
#include "Pipe.h"

class Game
{
public:
    static Game& getInstance()
    {
        static Game instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    bool Initialize();
    void Update();
    void Draw();
    void Clean();

    bool IsRunning() const { return isRunning; };
    int GetScreenWidth() const { return SCREEN_WIDTH; };
    int GetScreenHeight() const { return SCREEN_HEIGHT; };

private:
    Game() = default;

    //Screen dimension constants
    const int SCREEN_WIDTH = 480;
    const int SCREEN_HEIGHT = 750;

    bool isRunning = true;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Event event{};
    TTF_Font* font{};

    Bird bird;

    int frameCount = 0;

    int PIPE_GAP;
    int PIPE_WIDTH;
    int PIPE_SPEED;

    float groundSpeed = 100.0;

    bool isScored = false;
    int score = 0;
    int bestScore = 0;

    SDL_Surface* bgSurface, *groundSurface, *pipeSurface;
    SDL_Texture* bg, *ground, *pipeT;

    std::vector<Pipe> pipes;

public:
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;

};


#endif //FLAPPYBIRD_GAME_H
