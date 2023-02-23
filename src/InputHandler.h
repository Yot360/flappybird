//
// Created by yot on 23/02/23.
//

#ifndef FLAPPYBIRD_INPUTHANDLER_H
#define FLAPPYBIRD_INPUTHANDLER_H

#include <SDL.h>
#include <string.h>

class InputHandler
{
public:
    static InputHandler& getInstance()
    {
        static InputHandler instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    void Initialize();

    void updateKeyStates();
    bool isKeyDown(SDL_Scancode key);
    bool isKeyPressed(SDL_Scancode key);
    bool isKeyReleased(SDL_Scancode key);

private:
    InputHandler() {};

    const Uint8* keyStates;
    Uint8* keyHeldStates;
    int keyLength;

public:
    InputHandler(InputHandler const&) = delete;
    void operator=(InputHandler const&) = delete;

};


#endif //FLAPPYBIRD_INPUTHANDLER_H
