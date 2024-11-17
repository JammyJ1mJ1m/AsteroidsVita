#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>

#include "Vector.h"
#include <cstdio>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "Button.h"

#include "TextRenderer.h"
#include "Renderer.h"

#include "Player.h"
#include "Asteroid.h"
#include "Projectile.h"

#include "Managers/SceneManager.h"

// struct Directions
// {
//     Vector2f up;    // (0, -1)
//     Vector2f down;  // (0, 1)
//     Vector2f left;  // (-1, 0)
//     Vector2f right; // (1, 0)

//     Directions()
//         : up(0, -1), down(0, 1), left(-1, 0), right(1, 0)
//     {
//     }
// };

class App
{
    SceneManager *mSceneManager;

    // Directions mDirections;

    // Vector3f *mColour;
    Player *mPlayer;

    Renderer *mRenderer;

    SDL_GameController *controller;
    bool mIsRunning;
    // std::vector<Vector3f *> mColours;
    // int colourIndex;

    std::vector<Button *> mButtons;

    TextRenderer *textRenderer;

    // float stickVal;

    static App *theGame; // Static instance pointer
    int mHighScore;
    int LoadHighscore();
    bool SaveHighscore(const int pScore);

public:
    const int GetHighScore() const { return mHighScore; };
    static App *GetApp() { return theGame; }
    App();
    ~App();
    void run(const float pDeltaTime);
    void processInput();
    void SetColour(float r, float g, float b)
    {
        mRenderer->GetColour()->SetX(r);
        mRenderer->GetColour()->SetY(g);
        mRenderer->GetColour()->SetZ(b);
    }
    const bool GetRunning() { return mIsRunning; }
    void handleButtonPress(SceCtrlData &padData);
    TextRenderer *GetTextRenderer() { return textRenderer; };
    Renderer *GetRenderer() { return mRenderer; };
    Player *GetPlayer() { return mPlayer; }
    void QuitApp() { mIsRunning = false; }
    SceneManager *GetSceneManager() { return mSceneManager; }

    // sets all the button states back to being unpressed
    void ResetButtonStates();
};
