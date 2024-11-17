#include "App.h"
#include <psp2/ctrl.h>
#include "Scenes/GameScene.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/GameMenuScene.h"

App *App::theGame = nullptr;

App::App() : wasCrossPressed(false)
{
    mIsRunning = true;
    theGame = this;

    srand(time(0));
    mRenderer = new Renderer();
    mRenderer->Init();

    mPlayer = new Player();

    mButtons.push_back(new Button(SCE_CTRL_CROSS));

    // xButton = new Button(SCE_CTRL_CROSS);
    mButtons.push_back(new Button(SCE_CTRL_CIRCLE));
    // oButton = new Button(SCE_CTRL_CIRCLE);
    mButtons.push_back(new Button(SCE_CTRL_TRIANGLE));
    // triButton = new Button(SCE_CTRL_TRIANGLE);
    mButtons.push_back(new Button(SCE_CTRL_SQUARE));
    // squButton = new Button(SCE_CTRL_SQUARE);

    // L1Button = new Button(SCE_CTRL_L1);
    // R1Button = new Button(SCE_CTRL_R1);
    mButtons.push_back(new Button(SCE_CTRL_R1));

    // Dpad btns
    mButtons.push_back(new Button(SCE_CTRL_LEFT));
    // DLButton = new Button(SCE_CTRL_LEFT);
    mButtons.push_back(new Button(SCE_CTRL_RIGHT));
    // DRButton = new Button(SCE_CTRL_RIGHT);
    mButtons.push_back(new Button(SCE_CTRL_UP));
    // DUButton = new Button(SCE_CTRL_UP);
    mButtons.push_back(new Button(SCE_CTRL_DOWN));
    // DDButton = new Button(SCE_CTRL_DOWN);

    mButtons.push_back(new Button(SCE_CTRL_SELECT));
    // Select = new Button(SCE_CTRL_SELECT);

    textRenderer = new TextRenderer(mRenderer->GetRenderer(), "res/Orbitron-Regular.ttf", 24);

    mSceneManager = new SceneManager(this);
    // mSceneManager->PushScene(new GameScene());
    // mSceneManager->PushScene(new GameOverScene());
    mSceneManager->PushScene(new GameMenuScene());
}

void App::processInput()
{
    SceCtrlData padData;
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_DIGITAL);

    sceCtrlReadBufferPositive(0, &padData, 1);

    sceCtrlPeekBufferPositiveExt2(0, &padData, 1);

    handleButtonPress(padData);
}

void App::ResetButtonStates()
{
    for (auto &butt : mButtons)
    {
        butt->SetState(false);
    }
}

void App::handleButtonPress(SceCtrlData &padData)
{
    for (auto &butt : mButtons)
    {
        mSceneManager->OnKeyboard(butt, padData);
    }
    // if (triButton->CheckButtonDown(padData))
    // {
    //     if (mAsteroids.size() > 0)
    //     {
    //         indexer++;
    //         if (indexer > mAsteroids.size())
    //             indexer = 0;
    //     }
    // }

    // if (squButton->CheckButtonDown(padData))
    // {
    //     mSceneManager->OnKeyboard(squButton);

    //     // if (mPlayer->GetShotProjectiles() >= 5)
    //     //     return;

    //     // Projectile *proj = mPlayer->ShootProjectile();

    //     // proj->SetPosition(mPlayer->GetPos());
    //     // proj->SetRotation(mPlayer->GetRotation());
    //     // proj->UpdateVelocity(10);
    //     // mProjectiles.push_back(proj);
    // }

    // if (DLButton->CheckKey(padData))
    //     mSceneManager->OnKeyboard(DLButton);
    // //     mPlayer->SetRotation(mPlayer->GetRotation() - 3);

    // if (DRButton->CheckKey(padData))
    //     mSceneManager->OnKeyboard(DRButton);

    // //     mPlayer->SetRotation(mPlayer->GetRotation() + 3);

    // if (xButton->CheckKey(padData))
    //     mSceneManager->OnKeyboard(xButton);

    // mPlayer->SetSpeed(1);

    // if (Select->CheckButtonDown(padData))
    // mIsDebug = !mIsDebug;

    // if (oButton->CheckButtonDown(padData))
    //     mIsRunning = false;
}

// Function to draw a circle using the midpoint circle algorithm

void App::run(const float pDeltaTime)
{
    SDL_Color textColor = {255, 255, 255};
    textRenderer->renderText("Hallo welt!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, textColor, true);
    processInput();
    mRenderer->Render();

    mSceneManager->Render(mRenderer, pDeltaTime);

    mRenderer->EndRender();
}

App::~App()
{

    delete mPlayer;

    for (auto &butt : mButtons)
    {
        delete butt;
    }

    // delete xButton;
    // delete oButton;
    // delete triButton;
    // delete squButton;
    // delete DLButton;
    // delete DRButton;
    // delete DUButton;
    // delete DDButton;

    // delete Select;

    delete textRenderer;
    delete mColour;

    delete mRenderer;
}