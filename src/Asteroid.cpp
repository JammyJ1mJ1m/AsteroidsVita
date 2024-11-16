//
// Created by james on 11/7/24.
//

#include "Asteroid.h"
#include "Renderer.h"

Asteroid::Asteroid()
{
    mScale = 1.0f;
    mVelocity = new Vector2f(0, 0);

    int asID = rand() % 3;
  
    switch (asID)
    {
    case 1:
    mVerts.push_back({0, -45});    // top
    mVerts.push_back({-20, -35});  // top-left
    mVerts.push_back({-40, -10});  // left upper
    mVerts.push_back({-30, 15});   // left lower
    mVerts.push_back({-15, 40});   // bottom-left
    mVerts.push_back({10, 35});    // bottom
    mVerts.push_back({30, 15});    // bottom-right
    mVerts.push_back({35, -10});   // right lower
    mVerts.push_back({20, -30});   // right upper

    break;
case 2:
    mVerts.push_back({0, -40});    // top
    mVerts.push_back({-25, -25});  // top-left
    mVerts.push_back({-35, 0});    // left
    mVerts.push_back({-25, 25});   // bottom-left
    mVerts.push_back({0, 35});     // bottom
    mVerts.push_back({25, 25});    // bottom-right
    mVerts.push_back({35, 0});     // right
    mVerts.push_back({25, -20});   // bottom-right

    break;
case 3:
    mVerts.push_back({0, -30});    // top
    mVerts.push_back({-15, -25});  // top-left
    mVerts.push_back({-25, -10});  // left upper
    mVerts.push_back({-20, 5});    // left lower
    mVerts.push_back({-10, 25});   // bottom-left
    mVerts.push_back({5, 20});     // bottom
    mVerts.push_back({15, 10});    // bottom-right
    mVerts.push_back({20, -5});    // right lower
    mVerts.push_back({10, -20});   // right upper

    break;
default:
    mVerts.push_back({0, -50});    // top (shifted up from center)
    mVerts.push_back({-25, -25});  // top-left point
    mVerts.push_back({-37, 0});  // middle-left point
    mVerts.push_back({-12, 25}); // middle point on the left side
    mVerts.push_back({-50, 37}); // bottom-left point
    mVerts.push_back({0, 50});     // bottom center
    mVerts.push_back({37, 25});  // middle point on the right side
    mVerts.push_back({25, 0});     // top-right point
    mVerts.push_back({50, -25});   // top-right point
        break;
    }

    mFriction = 1;
    mPosition = new Vector2f(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2);
    mRotAngle = 0;
    mMaxSpeed = 5;

    SetRotation(rand() % 360);
    UpdateVelocity(1 + rand() % 5);
    mHasExpired = false;

    mColliderRadius = 30;
    mLives = 3;
}

void Asteroid::OnCollision()
{
    SetHasExpired(true);
}