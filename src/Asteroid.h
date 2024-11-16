#pragma once

#include "Model.h"

class Asteroid : public Model
{
    int mLives;
public:
    Asteroid();
    ~Asteroid() = default;
   void OnCollision() override;
   const int GetLives() {return mLives;}
    void SetLives(const int pLives) {mLives = pLives;}

};