//
// Created by yot on 23/02/23.
//

#ifndef FLAPPYBIRD_PIPE_H
#define FLAPPYBIRD_PIPE_H

#include <SDL.h>
#include <cstdlib>


class Pipe {
public:
    Pipe(int windowHeight, int pipeGap, int pipeWidth, int x);
    void move(int dx);
    SDL_Rect* getTopRect() ;
    SDL_Rect* getBottomRect() ;

    // Set whether the pipe has been passed by the bird
    void setPassed(bool passed) {
        passed_ = passed;
    }

    // Check whether the pipe has been passed by the bird
    bool isPassed() const {
        return passed_;
    }

private:
    int topPipeY;
    int bottomPipeY;
    SDL_Rect topRect;
    SDL_Rect bottomRect;

    bool passed_ = false; // Flag to track whether pipe has been passed by bird
};


#endif //FLAPPYBIRD_PIPE_H
