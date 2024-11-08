//
// Created by james on 11/7/24.
//
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "Vector.h"

#ifndef MODEL_H
#define MODEL_H

class Renderer;

class Model
{

protected:
  std::vector<SDL_Point> mVerts;
  Vector2f *mPosition;
  float mScale;
float mRotAngle;
Vector2f *mVelocity;

public:

  ~Model();


  void CheckBounds();
  void SetScale(float pScale) { mScale = pScale; }
  virtual void Draw(Renderer *pRenderer) = 0;
  virtual void UpdatePosition(const Vector2f &pDir) = 0;
};

#endif // MODEL_H
