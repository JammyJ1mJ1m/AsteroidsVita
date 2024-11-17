#pragma once

#include <SDL2/SDL.h>
#include "Vector.h"

constexpr int SCREEN_WIDTH = 960;
constexpr int SCREEN_HEIGHT = 544;

extern SDL_Rect fillRect; // Declare but don't define

class Renderer
{
 
    SDL_Renderer *renderer;
    SDL_Window *window;
    Vector3f *mColour;


public:
    Renderer()= default;
    ~Renderer();

void Init();
void Render();
void EndRender();
SDL_Renderer* GetRenderer() { return renderer;}
SDL_Window* GetWindow() { return window;}
Vector3f* GetColour() { return mColour;}

    
};