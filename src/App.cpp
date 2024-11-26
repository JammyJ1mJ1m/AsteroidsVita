#include "App.h"
#include <psp2/ctrl.h>
#include "Scenes/GameScene.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/GameMenuScene.h"

// For saving to disk
#include <psp2/io/dirent.h>
#include <psp2/io/stat.h>
#include <psp2/io/fcntl.h>
#include <stdio.h>
#include <string.h>
#define FILE_PATH "ux0:data/AsteroidsVita/highscore.txt"
#include "Managers/AudioManager.h"

App *App::theGame = nullptr;

App::App()
{
    mIsRunning = true;
    theGame = this;

    srand(time(0));
    mRenderer = new Renderer();
    mRenderer->Init();

    mPlayer = new Player();

    mButtons.push_back(new Button(SCE_CTRL_CROSS));

    mButtons.push_back(new Button(SCE_CTRL_CIRCLE));
    mButtons.push_back(new Button(SCE_CTRL_TRIANGLE));
    mButtons.push_back(new Button(SCE_CTRL_SQUARE));
    mButtons.push_back(new Button(SCE_CTRL_R1));
    mButtons.push_back(new Button(SCE_CTRL_LEFT));
    mButtons.push_back(new Button(SCE_CTRL_RIGHT));
    mButtons.push_back(new Button(SCE_CTRL_UP));
    mButtons.push_back(new Button(SCE_CTRL_DOWN));
    mButtons.push_back(new Button(SCE_CTRL_SELECT));

    textRenderer = new TextRenderer(mRenderer->GetRenderer(), "res/Orbitron-Regular.ttf", 24);

    mSceneManager = new SceneManager(this);
    // mSceneManager->PushScene(new GameScene());
    // mSceneManager->PushScene(new GameOverScene());
    mSceneManager->PushScene(new GameMenuScene());

    mHighScore = 0;
    mHighScore = LoadHighscore();

    AudioManager::GetInstance().LoadWav("ex", "app0:/res/Explosion.wav");
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
}

int App::LoadHighscore()
{
    SceUID file = sceIoOpen(FILE_PATH, SCE_O_RDONLY, 0777);
    if (file < 0)
    {
        printf("Failed to open file for reading. Returning 0 as default high score.\n");
        return 0; 
    }

    char buffer[32] = {0};
    sceIoRead(file, buffer, sizeof(buffer) - 1);

    sceIoClose(file);

    return atoi(buffer);
}

bool App::SaveHighscore(const int pScore)
{
    // We need to create a directory if it does not exist
    sceIoMkdir("ux0:data/AsteroidsVita", 0777);

    SceUID file = sceIoOpen(FILE_PATH, SCE_O_WRONLY | SCE_O_CREAT, 0777);
    if (file < 0)
    {
        return false;
    }

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", pScore);

    sceIoWrite(file, buffer, strlen(buffer));

    sceIoClose(file);
    return true;
}

void App::run(const float pDeltaTime)
{
    processInput();
    mRenderer->Render();
    mSceneManager->Update(pDeltaTime);
    mSceneManager->Render(mRenderer, pDeltaTime);
    mRenderer->EndRender();

    if (!mIsRunning)
    {
        int score = mPlayer->GetScore();
        if (score > mHighScore)
            SaveHighscore(mPlayer->GetScore());
    }
}

App::~App()
{

    delete mPlayer;

    for (auto &butt : mButtons)
    {
        delete butt;
    }

    delete textRenderer;
    delete mRenderer;
}