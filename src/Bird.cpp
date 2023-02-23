//
// Created by yot on 23/02/23.
//

#include <string>
#include "Bird.h"
#include "TTFManager.h"

Bird::Bird()
{

}

void Bird::Update()
{
    mBirdVel += mGravity;
    mBirdY += mBirdVel;

    if (InputHandler::getInstance().isKeyPressed(SDL_SCANCODE_SPACE)) {
        Jump();
    }

    if (InputHandler::getInstance().isKeyPressed(SDL_SCANCODE_G))
    {
        isGodMode = !isGodMode;
    }

    bird = {mBirdX, mBirdY, mBirdSize, mBirdSize};
}

void Bird::Draw(SDL_Renderer* renderer)
{
    SDL_Rect birdRect = { mBirdX, mBirdY, mBirdSize, mBirdSize }; // Create a rectangle for the bird

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set the color to white
    SDL_RenderFillRect(renderer, &birdRect); // Draw the bird square

}

void Bird::Jump()
{
    if (!isDead)
        mBirdVel = mJumpVel;
}

void Bird::Dead()
{
    isDead = true;
    mBirdVel = 0;
}

void Bird::Reset()
{
    mBirdY = 100.0f;
    mBirdX = 100.0f;
    mBirdVel = 0;
    isDead = false;
}
