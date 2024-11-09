//
// Created by james on 11/7/24.
//

#include "Player.h"
#include "Renderer.h"

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
    UpdateVelocity(0);
}