//
// Created by yot on 23/02/23.
//

#include "TTFManager.h"

void TTFManager::WriteText(SDL_Renderer* renderer, TTF_Font* font, int fontSize, std::string text, SDL_Color color, int x, int y)
{
    // Update font size
    TTF_SetFontSize(font, fontSize);

    // Get size of the text
    int textWidth, textHeight;
    TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);

    // Create surface and texture that will be drawn
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Create and SDL_Rect for where it will be drawn
    SDL_Rect dstRect = {
            x,
            y,
            textWidth,
            textHeight
    };

    // Draw to screen
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    // Free memory
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
