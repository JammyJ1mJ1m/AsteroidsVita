//
// Created by james on 11/7/24.
//

#include "Model.h"
#include "Renderer.h"

void Model::CheckBounds()
{
    // loops the object to opposite side of screen
    if (mPosition->GetX() < -50)
        mPosition->SetX(SCREEN_WIDTH + 50);

    if (mPosition->GetY() < -50)
        mPosition->SetY(SCREEN_HEIGHT + 50);

    if (mPosition->GetX() > SCREEN_WIDTH + 50)
        mPosition->SetX(-50);

    if (mPosition->GetY() > SCREEN_HEIGHT + 50)
        mPosition->SetY(-50);
}

SDL_Point Model::rotatePoint(SDL_Point point, Vector2f *pivot, double angle)
{
    // Convert angle to radians
    double rad = ToRad(mRotAngle);

    // Translate point to origin
    int translatedX = point.x - pivot->GetX();
    int translatedY = point.y - pivot->GetY();

    // Rotate using the rotation matrix
    int rotatedX = static_cast<int>(translatedX * cos(rad) - translatedY * sin(rad));
    int rotatedY = static_cast<int>(translatedX * sin(rad) + translatedY * cos(rad));

    // Translate back
    SDL_Point rotatedPoint = {static_cast<int>(rotatedX + pivot->GetX()), static_cast<int>(rotatedY + pivot->GetY())};

    return rotatedPoint;
}

void Model::SetRotation(const float pAngle)
{
    mRotAngle = pAngle;
    if (mRotAngle >= 360.0)
        mRotAngle -= 360.0;

    else if (mRotAngle <= 0)
        mRotAngle += 360;
}

Vector2f Model::GetForwardVector() const
{
    float rad = ToRad(mRotAngle - 90.0f);
    return Vector2f(cos(rad), sin(rad));
}

void Model::UpdateVelocity(float speed)
{
    Vector2f forward = GetForwardVector();

    mVelocity->SetX(mVelocity->GetX() + forward.GetX() * speed);
    mVelocity->SetY(mVelocity->GetY() + forward.GetY() * speed);

    mVelocity->ClampLength(mMaxSpeed);
}

void Model::SetSpeed(const float pSpeed)
{
    mSpeed = pSpeed;
    UpdateVelocity(mSpeed);
}

void Model::ApplyFriction(const float pFric)
{

    mVelocity->SetX(mVelocity->GetX() * pFric);
    mVelocity->SetY(mVelocity->GetY() * pFric);
}

void Model::Draw(Renderer *pRenderer)
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

void Model::Update(const float pDeltaTime)
{
    mPosition->SetX(mPosition->GetX() + mVelocity->GetX());
    mPosition->SetY(mPosition->GetY() + mVelocity->GetY());

    ApplyFriction(mFriction);
    CheckBounds();
}

Model::~Model()
{
    delete mVelocity;
    delete mPosition;
}