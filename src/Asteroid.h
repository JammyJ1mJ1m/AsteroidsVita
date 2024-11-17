#pragma once

#include "Model.h"

class Asteroid : public Model
{
    int mLives;
Vector2f SetRandomSpawnPosition(float centerX, float centerY, float radius);

public:
    Asteroid();
    ~Asteroid() = default;
   void OnCollision() override;
   const int GetLives() {return mLives;}
    void SetLives(const int pLives) {mLives = pLives;}

};