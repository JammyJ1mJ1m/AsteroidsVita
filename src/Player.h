#pragma once

#include "Model.h"

class Player : public Model
{
public:
    Player();
    ~Player() = default;

    void Draw(Renderer *pRenderer) override;
    void DrawWithRot(Renderer *pRenderer) ;
    void UpdatePosition(const Vector2f& pDir) override;

    Vector2f& GetPos() { return *mPosition;}
};