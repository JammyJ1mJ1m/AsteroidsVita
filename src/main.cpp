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

#include <chrono>

#define printf psvDebugScreenPrintf

int ConvertToSeconds(const int pTime)
{
  return pTime * 1000000;
}

int main(int argc, char *argv[])
{

  int targetFPS = 60;
  int frameTime = 1000 / targetFPS;

  App app;
  float dt = 0.0f;

  auto lastFrameTime = std::chrono::steady_clock::now();
  while (app.GetRunning())
  {
    auto currentFrameTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> deltaTime = currentFrameTime - lastFrameTime;
    dt = deltaTime.count();

    lastFrameTime = currentFrameTime;

    app.run(dt);

    SDL_Delay(frameTime);
  }

  sceKernelExitProcess(0);
  return 0;
}