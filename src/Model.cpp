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

    mVelocity->ClampLength(5);
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

Model::~Model()
{
    delete mPosition;
}