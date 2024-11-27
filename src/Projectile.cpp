#include "Projectile.h"
#include "Renderer.h"

Projectile::Projectile()
{
    mScale = 1.0f;
    mVelocity = Vector2f(0, 0);
    mVerts.push_back({-5, 5});
    mVerts.push_back({5, 5});
    mVerts.push_back({5, -5});
    mVerts.push_back({-5, -5});

    mFriction = 1;
    mPosition = Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    mRotAngle = 0;
    mMaxLifeTime = 5;
    mCurrentLifeTime = 0;
    mMaxSpeed = 10;
    mHasExpired = false;
    mColliderRadius = 5;
}

void Projectile::Update(const float pDeltaTime)
{
    mPosition.SetX(mPosition.GetX() + mVelocity.GetX());
    mPosition.SetY(mPosition.GetY() + mVelocity.GetY());

    ApplyFriction(mFriction);
    CheckBounds();
    mCurrentLifeTime += pDeltaTime;
}

void Projectile::OnCollision()
{
    SetHasExpired(true);
}