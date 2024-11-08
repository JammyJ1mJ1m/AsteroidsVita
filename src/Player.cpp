//
// Created by james on 11/7/24.
//

#include "Player.h"
#include "Renderer.h"

Player::Player()
{
    mScale = 0.25f;
    mVelocity = new Vector2f(0,0);
    mVerts.push_back({0, -100});   // top (shifted up from center)
    mVerts.push_back({-100, 100}); // bottom left (shifted down and left)
    mVerts.push_back({0, 75});     // middle (slightly above bottom center)
    mVerts.push_back({100, 100});

    mPosition = new Vector2f(SCREEN_WIDTH /2, SCREEN_HEIGHT/2);
}

void Player::Draw(Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer->GetRenderer(), 255, 255, 255, 255);

    SDL_RenderDrawLine(pRenderer->GetRenderer(),
                       mPosition->GetX() + mVerts[0].x * mScale, mPosition->GetY() + mVerts[0].y * mScale,
                       mPosition->GetX() + mVerts[1].x * mScale, mPosition->GetY() + mVerts[1].y * mScale);

    SDL_RenderDrawLine(pRenderer->GetRenderer(),
                       mPosition->GetX() + mVerts[1].x * mScale, mPosition->GetY() + mVerts[1].y * mScale,
                       mPosition->GetX() + mVerts[2].x * mScale, mPosition->GetY() + mVerts[2].y * mScale);

    SDL_RenderDrawLine(pRenderer->GetRenderer(),
                       mPosition->GetX() + mVerts[2].x * mScale, mPosition->GetY() + mVerts[2].y * mScale,
                       mPosition->GetX() + mVerts[3].x * mScale, mPosition->GetY() + mVerts[3].y * mScale);

    SDL_RenderDrawLine(pRenderer->GetRenderer(),
                       mPosition->GetX() + mVerts[3].x * mScale, mPosition->GetY() + mVerts[3].y * mScale,
                       mPosition->GetX() + mVerts[0].x * mScale, mPosition->GetY() + mVerts[0].y * mScale);
}



void Player::UpdatePosition(const Vector2f &pDir)
{
    float moveSpeed = 5; // How much the player moves per frame

    mPosition->SetX(mPosition->GetX() + pDir.GetX() * moveSpeed);
    mPosition->SetY(mPosition->GetY() + pDir.GetY() * moveSpeed);

CheckBounds();
}
