#pragma once

#include "Model.h"

class Projectile;

class Player : public Model
{
    int mShotProjectiles;
    int mScore;
    int mLives;

public:
    Player();
    ~Player() = default;
    inline const int GetShotProjectiles() { return mShotProjectiles; }
    inline void SetShotProjectiles(const int pShotProj) { mShotProjectiles = pShotProj; }
    inline const int GetScore() { return mScore; }
    inline const void SetScore(const int pScore) { mScore = pScore; }
    inline const int GetLives() { return mLives; }
    Projectile *ShootProjectile();
    void OnCollision() override;
};
