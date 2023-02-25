//
// Created by yot on 23/02/23.
//

#ifndef FLAPPYBIRD_BIRD_H
#define FLAPPYBIRD_BIRD_H

#include <SDL_ttf.h>
#include <SDL_image.h>
#include "InputHandler.h"
#include "ConfigHelper.h"

class Bird {

public:
    Bird();

    void LoadFromJson();

    void Jump();
    void Dead();
    void Reset();

    void Update();
    void Draw(SDL_Renderer* renderer);


    SDL_Rect* GetRect() { return &bird; }
    bool IsDead() { return isDead; }
    bool IsGodMode() { return isGodMode; }

private:

    //Screen dimension constants
    const int SCREEN_WIDTH = 480;
    const int SCREEN_HEIGHT = 750;

    float mGravity;
    float mJumpVel;
    int mBirdY = 100.0f;
    int mBirdX = 100.0f;
    float mBirdVel = 0.0f;
    int mBirdSizeW = 17*3;
    int mBirdSizeH = 12*3;

    SDL_Rect bird;
    bool isDead = false;
    bool isGodMode = false;

    SDL_Surface* birdSprites[3];
    int currentBirdSprite;
    Uint32 lastBirdAnimationTime;
};


#endif //FLAPPYBIRD_BIRD_H
