//
// Created by james on 11/7/24.
//

#include "Asteroid.h"
#include "Renderer.h"

Asteroid::Asteroid()
{
    mScale = 0.45f;
    mVelocity = new Vector2f(0, 0);
    mVerts.push_back({0, -100});  // top (shifted up from center)
    mVerts.push_back({-50, -50}); // top-left point
    mVerts.push_back({-75, 0});   // middle-left point
    mVerts.push_back({-25, 50});  // middle point on the left side
    mVerts.push_back({-100, 75}); // bottom-left point
    mVerts.push_back({0, 100});   // bottom center
    mVerts.push_back({75, 50});   // middle point on the right side
    mVerts.push_back({50, 0});    // top-right point
    mVerts.push_back({100, -50});

    mFriction = 1;
    mPosition = new Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    mRotAngle = 0;

    SetRotation(rand() % 360);
    UpdateVelocity(1 + rand() % 5);
}