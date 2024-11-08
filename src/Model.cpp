//
// Created by james on 11/7/24.
//

#include "Model.h"
#include "Renderer.h"


void Model::CheckBounds()
{
    // loops the object to opposite side of screen
    if (mPosition->GetX() < 0)
        mPosition->SetX(SCREEN_WIDTH);

    if (mPosition->GetY() < 0)
        mPosition->SetY(SCREEN_HEIGHT);

    if (mPosition->GetX() > SCREEN_WIDTH)
        mPosition->SetX(0);

    if (mPosition->GetY() > SCREEN_HEIGHT)
        mPosition->SetY(0);
}

Model::~Model()
{
    delete mPosition;
}