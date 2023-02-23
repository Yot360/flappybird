//
// Created by yot on 23/02/23.
//

#ifndef FLAPPYBIRD_BIRD_H
#define FLAPPYBIRD_BIRD_H

#include <SDL_ttf.h>
#include "InputHandler.h"

class Bird {

public:
    Bird();

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

    const float mGravity = 0.15f;
    float mJumpVel = -5.0f;
    int mBirdY = 100.0f;
    int mBirdX = 100.0f;
    float mBirdVel = 0.0f;
    int mBirdSize = 50;

    SDL_Rect bird;
    bool isDead = false;
    bool isGodMode = false;
};


#endif //FLAPPYBIRD_BIRD_H
