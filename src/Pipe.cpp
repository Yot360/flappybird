//
// Created by yot on 23/02/23.
//

#include "Pipe.h"

Pipe::Pipe(int windowHeight, int pipeGap, int pipeWidth, int x) {
    // Generate a random y position for the top pipe
    topPipeY = rand() % (windowHeight - pipeGap - 120) - 160*3;

    // Calculate the y position of the bottom pipe
    bottomPipeY = topPipeY + pipeGap;

    // Create the SDL_Rect for the top pipe
    topRect = { x, topPipeY, pipeWidth, 160*3 };

    // Create the SDL_Rect for the bottom pipe
    bottomRect = { x, bottomPipeY + 160*3, pipeWidth, 160*3 };
}

void Pipe::move(int dx) {
    topRect.x -= dx;
    bottomRect.x -= dx;
}

SDL_Rect* Pipe::getTopRect() {
    return &topRect;
}

SDL_Rect* Pipe::getBottomRect() {
    return &bottomRect;
}



