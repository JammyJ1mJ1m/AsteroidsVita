#include "GameOverScene.h"

#include <sstream>
#include "../Renderer.h"
#include "../App.h"
#include "../TextRenderer.h"
// #include <chrono>

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

/// <summary>
/// All game objects are created here and members are initialised
/// </summary>
void GameOverScene::Initialise()
{
}

void GameOverScene::OnKeyboard(Button *pButton, SceCtrlData &padData)
{
    if (pButton->GetKey() == SCE_CTRL_CIRCLE && pButton->CheckKey(padData))
    {
        App::GetApp()->GetSceneManager()->PopScene();

    }
}

void GameOverScene::Update(double deltaTime)
{
}

void GameOverScene::Render(Renderer *pRenderer, const float pDeltaTime)
{
    SDL_Color textColor = {200, 50, 50};

    App::GetApp()->GetTextRenderer()->renderText("GAME OVER!!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, textColor, true);
}