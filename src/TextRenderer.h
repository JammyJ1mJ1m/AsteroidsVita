
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


class TextRenderer {
public:
    TextRenderer(SDL_Renderer* renderer, const char* fontPath, int fontSize);
    ~TextRenderer();

    void renderText(const char* text, int x, int y, SDL_Color color, const bool pIsCentered = false);

private:
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
};
