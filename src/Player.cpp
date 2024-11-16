//
// Created by james on 11/7/24.
//

#include "Player.h"
#include "Renderer.h"
#include "Projectile.h"

Player::Player()
{
    mScale = 0.15f;
    mVelocity = new Vector2f(0, 0);
    mVerts.push_back({0, -100});   // top (shifted up from center)
    mVerts.push_back({-100, 100}); // bottom left (shifted down and left)
    mVerts.push_back({0, 75});     // middle (slightly above bottom center)
    mVerts.push_back({100, 100});
    mFriction = 0.98f;

    mPosition = new Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    mRotAngle = 0;
    mMaxSpeed = 5;
    mHasExpired = false;
mColliderRadius = 10;
mLives = 3;
    UpdateVelocity(0);
}

Projectile *Player::ShootProjectile()
{
    mShotProjectiles++;
    Projectile *proj = new Projectile();

    return proj;
}

void Player::OnCollision()
{
    if (mLives > 1)
    {
        mLives--;
        SetPosition(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
        delete mVelocity;
        mVelocity = new Vector2f(0,0);
    }
    else
        SetHasExpired(true);
}