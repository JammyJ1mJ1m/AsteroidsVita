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

struct Star
{
    Vector2f pos;
    Vector3f col;
};

struct Directions
{
    Vector2f up;    // (0, -1)
    Vector2f down;  // (0, 1)
    Vector2f left;  // (-1, 0)
    Vector2f right; // (1, 0)

    Directions()
        : up(0, -1), down(0, 1), left(-1, 0), right(1, 0)
    {
    }
};

class App
{
    Directions mDirections;

    Vector3f *mColour;
    Player *mPlayer;

    std::vector<Asteroid *> mAsteroids;


std::vector<Projectile*> mProjectiles;


    Renderer *mRenderer;

    SDL_GameController *controller;
    bool mIsRunning;
    std::vector<Vector3f *> mColours;
    int colourIndex;
    Uint8 previousButtonState;
    bool wasCrossPressed;
    bool wasCirclePressed;

    // shape buttons
    Button *xButton;
    Button *oButton;
    Button *triButton;
    Button *squButton;

    // bumpers
    // Button *L1Button;
    // Button *R1Button;

    // Dpad btns
    Button *DLButton;
    Button *DRButton;
    Button *DUButton;
    Button *DDButton;

    Button *Select;

    TextRenderer *textRenderer;

    bool mIsDebug;

    float stickVal;
    int indexer;
    std::vector<Star> mBGStars;

public:
    App();
    void CreateAsteroids();
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
    void CheckCollisions();
};
