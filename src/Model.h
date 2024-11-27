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
  Vector2f mPosition;
  float mScale;
  float mRotAngle;
  Vector2f mVelocity;
  float mSpeed;
  float mFriction;
  float mMaxSpeed;
  bool mHasExpired;
  float mColliderRadius;

public:
  ~Model();

  void SetMaxSpeed(const float pSpeed) { mMaxSpeed = pSpeed; }
  const float GetMaxSpeed() { return mMaxSpeed; }
  inline void SetScale(const float pScale) { mScale = pScale; }
  inline const float GetScale() { return mScale; }
  Vector2f &GetPos() { return mPosition; }
  void SetPosition(Vector2f pPos) { mPosition = Vector2f(pPos.GetX(), pPos.GetY()); }
  void SetRotation(const float pAngle);
  const float GetRotation() { return mRotAngle; }
  Vector2f GetForwardVector() const;
  void SetSpeed(const float pSpeed);
  void CheckBounds();
  void Draw(Renderer *pRenderer);
  virtual void Update(const float pDeltaTime);
  Vector2f Rotate(const Vector2f &point);
  SDL_Point rotatePoint(SDL_Point point, Vector2f *pivot, double angle);
  void UpdateVelocity(float speed);
  void ApplyFriction(const float pFric);
  void SetHasExpired(const bool pHasExpired) { mHasExpired = pHasExpired; };
  const bool GetHasExpired() { return mHasExpired; }
  const int GetColliderRadius() { return mColliderRadius; };
  void SetColliderRadius(const int pRadius) { mColliderRadius = pRadius; }
  virtual void OnCollision() = 0;
};

#endif // MODEL_H
