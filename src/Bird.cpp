//
// Created by yot on 23/02/23.
//

#include <string>
#include "Bird.h"
#include "TTFManager.h"

Bird::Bird()
{
    birdSprites[0] = IMG_Load("Assets/bird1.png");
    birdSprites[1] = IMG_Load("Assets/bird2.png");
    birdSprites[2] = IMG_Load("Assets/bird3.png");

    currentBirdSprite = 0;
    lastBirdAnimationTime = SDL_GetTicks();
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

    const int BIRD_ANIMATION_SPEED = 100; // update bird sprite every 100 milliseconds

    Uint32 currentTicks = SDL_GetTicks();
    if (currentTicks - lastBirdAnimationTime >= BIRD_ANIMATION_SPEED) {
        // update bird sprite
        currentBirdSprite = (currentBirdSprite + 1) % 3;
        lastBirdAnimationTime = currentTicks;
    }

    bird = {mBirdX, mBirdY, mBirdSizeW, mBirdSizeH};
}

void Bird::Draw(SDL_Renderer* renderer)
{

    // Calculate the rotation angle based on the bird's velocity
    double rotationAngle = (mBirdVel > 0) ? 45 : -45;
    rotationAngle *= (mBirdVel / 7);

    // Set the center point of rotation
    SDL_Point center = { mBirdSizeW / 2, mBirdSizeH / 2 };

    SDL_Rect birdRect = { mBirdX, mBirdY, mBirdSizeW, mBirdSizeH }; // Create a rectangle for the bird

    SDL_Texture* birdT = SDL_CreateTextureFromSurface(renderer, birdSprites[currentBirdSprite]);

    // Render the sprite with rotation
    SDL_RenderCopyEx(renderer, birdT, NULL, &birdRect, rotationAngle, &center, SDL_FLIP_NONE);
    //SDL_RenderCopy(renderer, birdT, nullptr, &birdRect);

    SDL_DestroyTexture(birdT);
}

void Bird::Jump()
{
    if (!isDead)
        mBirdVel = mJumpVel;
}

void Bird::Dead()
{
    mBirdVel = 0;
    isDead = true;
}

void Bird::Reset()
{
    mBirdY = 100.0f;
    mBirdX = 100.0f;
    mBirdVel = 0;
    isDead = false;
}

void Bird::LoadFromJson()
{
    mGravity = ConfigHelper::getInstance().GetGravity();
    mJumpVel = ConfigHelper::getInstance().GetJumpVelocity();
}
