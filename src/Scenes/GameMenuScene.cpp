#include "GameMenuScene.h"

#include <sstream>
#include "../Renderer.h"
#include "../App.h"
#include "../TextRenderer.h"
#include "GameScene.h"
// #include <chrono>

GameMenuScene::GameMenuScene()
{
    UIIndex = 1;
    UIItems = 2;
}

GameMenuScene::~GameMenuScene()
{
}

/// <summary>
/// All game objects are created here and members are initialised
/// </summary>
void GameMenuScene::Initialise()
{
    textRenderer = new TextRenderer(App::GetApp()->GetRenderer()->GetRenderer(), "res/Orbitron-Regular.ttf", 48);
}

void GameMenuScene::OnKeyboard(Button *pButton, SceCtrlData &padData)
{
    // Up, down and x buttons
    if (pButton->GetKey() == SCE_CTRL_UP && pButton->CheckButtonDown(padData))
    {
        UIIndex--;
        if (UIIndex <= 0)
            UIIndex = UIItems;
    }
    if (pButton->GetKey() == SCE_CTRL_DOWN && pButton->CheckButtonDown(padData))
    {
        UIIndex++;
        if (UIIndex > UIItems)
            UIIndex = 1;
    }

    if (pButton->GetKey() == SCE_CTRL_CROSS && pButton->CheckButtonDown(padData))
    {
        if (UIIndex == 1)
        {
            App::GetApp()->ResetButtonStates();
            App::GetApp()->GetSceneManager()->PushScene(new GameScene());
        }
        // add game scene to scene stack
        if (UIIndex == 2)
            // quit game
            App::GetApp()->QuitApp();
    }
}

void GameMenuScene::Update(double deltaTime)
{
}

void GameMenuScene::Render(Renderer *pRenderer, const float pDeltaTime)
{
    SDL_Color textColor = {255, 255, 255};

    textRenderer->renderText("Asteroids Vita!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, textColor, true);

    SDL_Color highlightColor = {130, 130, 255, 255}; // Red for highlighting

    SDL_Color playColor = (UIIndex == 1) ? highlightColor : textColor;
    App::GetApp()->GetTextRenderer()->renderText("Play", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, playColor, true);

    SDL_Color quitColor = (UIIndex == 2) ? highlightColor : textColor;
    App::GetApp()->GetTextRenderer()->renderText("Quit", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, quitColor, true);
}