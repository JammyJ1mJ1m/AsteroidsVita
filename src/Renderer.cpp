#include "Renderer.h"


SDL_Rect fillRect = {SCREEN_WIDTH / 4,
                     SCREEN_HEIGHT / 4,
                     SCREEN_WIDTH / 2,
                     SCREEN_HEIGHT / 2};

void Renderer::Init()
{
        SDL_Init(SDL_INIT_VIDEO); // Initialize SDL Video subsystem
    window = SDL_CreateWindow("Asteroids Vita",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);

    mColour = new Vector3f(0,0,0);
}
void Renderer::Render()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


}

void Renderer::EndRender()
{
    SDL_RenderPresent(renderer);
}

Renderer::~Renderer()
{
        SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
