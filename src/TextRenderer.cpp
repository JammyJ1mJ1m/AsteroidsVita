
#include "TextRenderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>


TextRenderer::TextRenderer(SDL_Renderer* renderer, const char* fontPath, int fontSize)
    : mRenderer(renderer), mFont(nullptr)
{
    if (TTF_Init() == -1) {
        //throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }

    mFont = TTF_OpenFont(fontPath, fontSize);
    if (!mFont) {
        //throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
    }
}

TextRenderer::~TextRenderer() {
    TTF_CloseFont(mFont);
    TTF_Quit();
}

void TextRenderer::renderText(const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text, color);
    if (!textSurface) {
        SDL_Log("Failed to create text surface: %s", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if (!textTexture) {
        SDL_Log("Failed to create text texture: %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(mRenderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}
