#include "Projectile.h"
#include "Renderer.h"

Projectile::Projectile()
{
    mScale = 1.0f;
    mVelocity = new Vector2f(0, 0);
    mVerts.push_back({-5, 5});  // top (shifted up from center)
    mVerts.push_back({5, 5}); // top-left point
    mVerts.push_back({5, -5});   // middle-left point
    mVerts.push_back({-5, -5});  // middle point on the left side


    mFriction = 1;
    mPosition = new Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    mRotAngle = 0;

    SetRotation(rand() % 360);
    UpdateVelocity(1 + rand() % 5);
}