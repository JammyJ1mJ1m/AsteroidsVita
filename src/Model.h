//
// Created by james on 11/7/24.
//
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "Vector.h"

#ifndef MODEL_H
#define MODEL_H

constexpr float PI = 3.141592f;

// converts degrees to radians
constexpr float ToRad(float angle)
{
  return angle * (PI / 180.0f);
}
class Renderer;

class Model
{

protected:
  std::vector<SDL_Point> mVerts;
  Vector2f *mPosition;
  float mScale;
  float mRotAngle;
  Vector2f *mVelocity;
  float mSpeed;
  float mFriction;

public:
  ~Model();

  void CheckBounds();
  void SetScale(float pScale) { mScale = pScale; }
  
  void Draw(Renderer *pRenderer);
    Vector2f& GetPos() { return *mPosition;}

  virtual void UpdatePosition();
  Vector2f Rotate(const Vector2f &point);
  SDL_Point rotatePoint(SDL_Point point, Vector2f *pivot, double angle);
  Vector2f GetForwardVector() const;
  void UpdateVelocity(float speed);
  void SetSpeed(const float pSpeed);
  void ApplyFriction(const float pFric);

  void SetRotation(const float pAngle);

  const float GetRotation() { return mRotAngle; }
};

#endif // MODEL_H
