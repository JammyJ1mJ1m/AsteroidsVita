#include "App.h"
#include <psp2/ctrl.h>

App::App() : wasCrossPressed(false)
{
    srand(time(0));
    mRenderer = new Renderer();
    mRenderer->Init();

    mPlayer = new Player();

    int initialAsteroidCount = 4;
    for (size_t i = 0; i < initialAsteroidCount; i++)
    {
        mAsteroids.push_back(new Asteroid());
    }

    mProjectile = new Projectile();

    xButton = new Button(SCE_CTRL_CROSS);
    oButton = new Button(SCE_CTRL_CIRCLE);
    triButton = new Button(SCE_CTRL_TRIANGLE);
    squButton = new Button(SCE_CTRL_SQUARE);

    // L1Button = new Button(SCE_CTRL_L1);
    // R1Button = new Button(SCE_CTRL_R1);

    // Dpad btns
    DLButton = new Button(SCE_CTRL_LEFT);
    DRButton = new Button(SCE_CTRL_RIGHT);
    DUButton = new Button(SCE_CTRL_UP);
    DDButton = new Button(SCE_CTRL_DOWN);

    Select = new Button(SCE_CTRL_SELECT);

    textRenderer = new TextRenderer(mRenderer->GetRenderer(), "res/Orbitron-Regular.ttf", 24);
    mIsDebug = false;
}

void App::processInput()
{
    SceCtrlData padData;
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_DIGITAL);

    sceCtrlReadBufferPositive(0, &padData, 1);

    handleButtonPress(padData);
}

void App::handleButtonPress(SceCtrlData &padData)
{

    if (xButton->CheckButtonDown(padData))
        SetColour(rand() % 256, rand() % 256, rand() % 256); // Random RGB color

    // if (L1Button->CheckKey(padData))
    //     SetColour(255, 0, 0);

    if (DLButton->CheckKey(padData))
        mPlayer->SetRotation(mPlayer->GetRotation() - 3);

    if (DRButton->CheckKey(padData))
        mPlayer->SetRotation(mPlayer->GetRotation() + 3);

    if (xButton->CheckKey(padData))
        mPlayer->SetSpeed(1);

    if (Select->CheckButtonDown(padData))
        mIsDebug = !mIsDebug;

    if (oButton->CheckButtonDown(padData))
        mIsRunning = false;
}

void App::run()
{
    processInput();
#pragma region Main rendering
    mRenderer->Render();

    mPlayer->UpdatePosition();
    mPlayer->Draw(mRenderer);

    for (auto &asteroid : mAsteroids)
    {
        asteroid->UpdatePosition();
        asteroid->Draw(mRenderer);
    }

    mProjectile->UpdatePosition();
        mProjectile->Draw(mRenderer);

#pragma endregion

#pragma region Boundary drawing
    SDL_SetRenderDrawColor(mRenderer->GetRenderer(), 255, 0, 0, 255);
    SDL_RenderDrawLine(mRenderer->GetRenderer(), 0, SCREEN_HEIGHT, 0, 0);                                    // Line from bottom-left to top-left
    SDL_RenderDrawLine(mRenderer->GetRenderer(), 0, 0, SCREEN_WIDTH, 0);                                     // Line from top-left to top-right
    SDL_RenderDrawLine(mRenderer->GetRenderer(), SCREEN_WIDTH - 1, 0, SCREEN_WIDTH, SCREEN_HEIGHT);          // Line from top-right to bottom-right
    SDL_RenderDrawLine(mRenderer->GetRenderer(), SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, SCREEN_HEIGHT - 1); // Line from bottom-right to bottom-left
#pragma endregion

    SDL_Color textColor = {255, 255, 255};
    textRenderer->renderText("000", 10, 10, textColor);

#pragma region Debug printing
    if (mIsDebug)
    {
        textRenderer->renderText(xButton->GetState().c_str(), 50, 100, textColor);
        float x = mPlayer->GetPos().GetX();
        float y = mPlayer->GetPos().GetY();
        std::string t1 = "Pos: " + std::to_string(x) + " : " + std::to_string(y);
        textRenderer->renderText(t1.c_str(), 50, 150, textColor);

        float r = mPlayer->GetRotation();
        std::string t2 = "Rot: " + std::to_string(r);
        textRenderer->renderText(t2.c_str(), 50, 200, textColor);

        SDL_SetRenderDrawColor(mRenderer->GetRenderer(), 255, 0, 255, 255);
        SDL_RenderDrawPoint(mRenderer->GetRenderer(), static_cast<int>(x), static_cast<int>(y)); // Convert to integer since pixel coordinates are integers
    }
#pragma endregion
    mRenderer->EndRender();
}

App::~App()
{
    for (auto &asteroid : mAsteroids)
    {
        delete asteroid;
    }
    delete mPlayer;

    delete xButton;
    delete oButton;
    delete triButton;
    delete squButton;
    delete DLButton;
    delete DRButton;
    delete DUButton;
    delete DDButton;

    delete Select;

    delete textRenderer;
    delete mColour;

    delete mRenderer;
}