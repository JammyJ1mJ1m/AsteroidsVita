#include "ControlsScene.h"

#include <sstream>
#include "../Renderer.h"
#include "../App.h"
#include "../TextRenderer.h"
// #include <chrono>

ControlsScene::ControlsScene()
{
}

ControlsScene::~ControlsScene()
{
}

/// <summary>
/// All game objects are created here and members are initialised
/// </summary>
void ControlsScene::Initialise()
{
}

void ControlsScene::OnKeyboard(Button *pButton, SceCtrlData &padData)
{
    if (pButton->GetKey() == SCE_CTRL_CIRCLE && pButton->CheckKey(padData))
    {
        App::GetApp()->GetSceneManager()->PopScene();

    }
}

void ControlsScene::Update(double deltaTime)
{
}

void ControlsScene::Render(Renderer *pRenderer, const float pDeltaTime)
{
    SDL_Color textColor = {200, 200, 200};
    App::GetApp()->GetTextRenderer()->renderText("Shoot: square", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, textColor, true);

    App::GetApp()->GetTextRenderer()->renderText("Move Forward: R1", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, textColor, true);
    App::GetApp()->GetTextRenderer()->renderText("Rotate: D-Pad left / D-Pad right", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, textColor, true);
}