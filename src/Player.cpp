//
// Created by james on 11/7/24.
//

#include "Player.h"
#include "Renderer.h"

Player::Player()
{
    mScale = 0.25f;
    mVelocity = new Vector2f(0, 0);
    mVerts.push_back({0, -100});   // top (shifted up from center)
    mVerts.push_back({-100, 100}); // bottom left (shifted down and left)
    mVerts.push_back({0, 75});     // middle (slightly above bottom center)
    mVerts.push_back({100, 100});

    mPosition = new Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    mRotAngle = 0;
}

void Player::Draw(Renderer *pRenderer)
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

void Player::DrawWithRot(Renderer *pRenderer)
{
    Vector2f modelCenter(0, 0);
    for (const auto &vertex : mVerts)
    {
        modelCenter.SetX(modelCenter.GetX() + vertex.x);
        modelCenter.SetY(modelCenter.GetY() + vertex.y);
    }
    modelCenter.SetX(modelCenter.GetX() / mVerts.size());
    modelCenter.SetY(modelCenter.GetY() / mVerts.size());

    std::vector<SDL_Point> rotatedVertices;
    for (const auto &vertex : mVerts)
    {
        SDL_Point rotated = rotatePoint(vertex, &modelCenter, mRotAngle);
        rotated.x = mPosition->GetX() + rotated.x * mScale;
        rotated.y = mPosition->GetY() + rotated.y * mScale;
        rotatedVertices.push_back(rotated);
    }

    SDL_SetRenderDrawColor(pRenderer->GetRenderer(), 255, 255, 255, 255);
    for (size_t i = 0; i < rotatedVertices.size(); ++i)
    {
        SDL_RenderDrawLine(pRenderer->GetRenderer(),
                           rotatedVertices[i].x, rotatedVertices[i].y,
                           rotatedVertices[(i + 1) % rotatedVertices.size()].x,
                           rotatedVertices[(i + 1) % rotatedVertices.size()].y);
    }
}

void Player::UpdatePosition(const Vector2f &pDir)
{
    mPosition->SetX(mPosition->GetX() + mVelocity->GetX());
    mPosition->SetY(mPosition->GetY() + mVelocity->GetY());
    
    ApplyFriction(0.98f);
    CheckBounds();
}
