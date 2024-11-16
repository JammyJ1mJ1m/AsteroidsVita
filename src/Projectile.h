#pragma once

#include "Model.h"

class Projectile : public Model
{
    float mMaxLifeTime;
    float mCurrentLifeTime;

public:
    Projectile();
    ~Projectile() = default;

    const float GetMaxLifeTime() { return mMaxLifeTime; }
    const float GetCurrentLifeTime() { return mCurrentLifeTime; }

    void Update(const float pDeltaTime) override;

    void OnCollision() override;
};