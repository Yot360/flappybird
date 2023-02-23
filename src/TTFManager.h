//
// Created by yot on 23/02/23.
//

#ifndef FLAPPYBIRD_TTFMANAGER_H
#define FLAPPYBIRD_TTFMANAGER_H

#include <SDL_ttf.h>
#include <string>

class TTFManager
{
public:
    static TTFManager& getInstance()
    {
        static TTFManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    void WriteText(SDL_Renderer* renderer, TTF_Font* font, int fontSizen, std::string text, SDL_Color color, int x, int y);

private:
    TTFManager() = default;

public:
    TTFManager(TTFManager const&) = delete;
    void operator=(TTFManager const&) = delete;

};


#endif //FLAPPYBIRD_TTFMANAGER_H
