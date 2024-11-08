//
// Created by james on 11/4/24.
//

#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <SDL2/SDL.h>

#include <cstdio>

#include <sstream>
#include <vector>

#include "Player.h"

#include "App.h"

#define printf psvDebugScreenPrintf

int ConvertToSeconds(const int pTime)
{
  return pTime * 1000000;
}

int main(int argc, char *argv[])
{
int targetFPS = 60;
int frameTime = 1000/targetFPS;



  App app;

  app.run();



  while (app.GetRunning())
  {
    app.run(); // Process input and render a frame

    // Add a small delay to control the frame rate if needed
    SDL_Delay(frameTime); // Approximately 60 FPS (1000ms / 60 ≈ 16ms per frame)
  }

  sceKernelExitProcess(0);
  return 0;
}