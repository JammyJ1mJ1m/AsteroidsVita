//
// Created by james on 11/7/24.
//

#include "Player.h"
#include "Renderer.h"
#include "Projectile.h"

// For saving to disk
#include <psp2/io/dirent.h>
#include <psp2/io/stat.h>
#include <psp2/io/fcntl.h>
#include <stdio.h>
#include <string.h>
#define FILE_PATH "ux0:data/AsteroidsVita/highscore.txt"
#include "Managers/AudioManager.h"

Player::Player()
{
    mScale = 0.15f;
    mVelocity = Vector2f(0, 0);
    mVerts.push_back({0, -100});   // top (shifted up from center)
    mVerts.push_back({-100, 100}); // bottom left (shifted down and left)
    mVerts.push_back({0, 75});     // middle (slightly above bottom center)
    mVerts.push_back({100, 100});
    mFriction = 0.98f;
    mColliderRadius = 10;
    mMaxSpeed = 5;

    ResetPlayer();
}

void Player::ResetPlayer()
{
    mPosition = Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    mRotAngle = 0;
    mHasExpired = false;
    mLives = 3;
    UpdateVelocity(0);
}

Projectile *Player::ShootProjectile()
{
    mShotProjectiles++;
    Projectile *proj = new Projectile();

    return proj;
}

void Player::OnCollision()
{
    if (mLives > 1)
        mLives--;

    else
    {
        SetHasExpired(true);
        SaveHighscore();
        SetScore(0);
    }

    mTimeAlive = 0.0f;
    SetPosition(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    
    mVelocity = Vector2f(0, 0);
    mShotProjectiles = 0;
}

void Player::Update(const float pDelta)
{
    mPosition.SetX(mPosition.GetX() + mVelocity.GetX());
    mPosition.SetY(mPosition.GetY() + mVelocity.GetY());

    ApplyFriction(mFriction);
    CheckBounds();

    mTimeAlive += pDelta;
    if(mTimeAlive >= 60.0f && ( mLives < 3 && mLives > 0) )
    {
        mTimeAlive = 0.0f;
        mLives++;
    }
}

bool Player::SaveHighscore()
{
    // We need to create a directory if it does not exist
    sceIoMkdir("ux0:data/AsteroidsVita", 0777);

    SceUID file = sceIoOpen(FILE_PATH, SCE_O_WRONLY | SCE_O_CREAT, 0777);
    if (file < 0)
    {
        return false;
    }

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", GetScore());

    sceIoWrite(file, buffer, strlen(buffer));

    sceIoClose(file);
    return true;
}