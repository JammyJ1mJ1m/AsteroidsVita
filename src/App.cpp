#include "App.h"
#include <psp2/ctrl.h>

App::App() : wasCrossPressed(false)
{
    indexer = 0;
    srand(time(0));
    mRenderer = new Renderer();
    mRenderer->Init();

    mPlayer = new Player();

    float starCount = 50;
    for (size_t i = 0; i < starCount; i++)
    {
        Star star;
        star.pos = Vector2f(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
        star.col = Vector3f(25 + (rand() % 180), 25 + (rand() % 180), 25 + (rand() % 180), 255);
        mBGStars.push_back(star);

        /* code */
    }

    CreateAsteroids();

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

void App::CreateAsteroids()
{
    int initialAsteroidCount = 4;
    for (size_t i = 0; i < initialAsteroidCount; i++)
    {
        mAsteroids.push_back(new Asteroid());
    }
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

    if (triButton->CheckButtonDown(padData))
    {
        if (mAsteroids.size() > 0)
        {
            indexer++;
            if (indexer > mAsteroids.size())
                indexer = 0;
        }
    }

    if (squButton->CheckButtonDown(padData))
    {
        if (mPlayer->GetShotProjectiles() >= 5)
            return;

        Projectile *proj = mPlayer->ShootProjectile();

        proj->SetPosition(mPlayer->GetPos());
        proj->SetRotation(mPlayer->GetRotation());
        proj->UpdateVelocity(10);
        mProjectiles.push_back(proj);
    }

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

// Function to draw a circle using the midpoint circle algorithm
void DrawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{
    int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x; // Decision variable for midpoint circle algorithm

    while (y <= x)
    {
        // Draw the points using symmetry
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);

        y++;
        if (decisionOver2 <= 0)
        {
            decisionOver2 += 2 * y + 1; // Change in decision criterion for y -> y+1
        }
        else
        {
            x--;
            decisionOver2 += 2 * (y - x) + 1; // Change for y -> y+1, x -> x-1
        }
    }
}

void App::run(const float pDeltaTime)
{
    SDL_Color textColor = {255, 255, 255};

    processInput();
    mRenderer->Render();

    if (mPlayer->GetHasExpired())
    {
        textRenderer->renderText("GAME OVER!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, textColor, true);
    }
    else
    {

#pragma region Main rendering

        mPlayer->Update(pDeltaTime);
        mPlayer->Draw(mRenderer);
        if (mIsDebug)
            DrawCircle(mRenderer->GetRenderer(), mPlayer->GetPos().GetX(), mPlayer->GetPos().GetY(), mPlayer->GetColliderRadius());

        for (size_t i = 0; i < mAsteroids.size(); i++)
        // for (auto &asteroid : mAsteroids)
        {
            SDL_SetRenderDrawColor(mRenderer->GetRenderer(), 255, 0, 0, 255);
            if (i == indexer)
                SDL_SetRenderDrawColor(mRenderer->GetRenderer(), 255, 0, 255, 255);
            if (mIsDebug)
                DrawCircle(mRenderer->GetRenderer(), mAsteroids[i]->GetPos().GetX(), mAsteroids[i]->GetPos().GetY(), mAsteroids[i]->GetColliderRadius());
            mAsteroids[i]->Update(pDeltaTime);
            mAsteroids[i]->Draw(mRenderer);
        }

        for (auto &proj : mProjectiles)
        {
            SDL_SetRenderDrawColor(mRenderer->GetRenderer(), 255, 0, 0, 255);
            if (mIsDebug)
                DrawCircle(mRenderer->GetRenderer(), proj->GetPos().GetX(), proj->GetPos().GetY(), proj->GetColliderRadius());
            if (proj->GetCurrentLifeTime() >= proj->GetMaxLifeTime())
            {
                proj->SetHasExpired(true);
                continue;
            }
            proj->Update(pDeltaTime);
            proj->Draw(mRenderer);
        }
        CheckCollisions();

        for (auto &star : mBGStars)
        {
            SDL_SetRenderDrawColor(mRenderer->GetRenderer(), star.col.GetX(), star.col.GetY(), star.col.GetZ(), 1);
            SDL_RenderDrawPoint(mRenderer->GetRenderer(), star.pos.GetX(), star.pos.GetY());
        }

#pragma endregion

#pragma region Boundary drawing
        // SDL_SetRenderDrawColor(mRenderer->GetRenderer(), 255, 0, 0, 255);
        // SDL_RenderDrawLine(mRenderer->GetRenderer(), 0, SCREEN_HEIGHT, 0, 0);                                    // Line from bottom-left to top-left
        // SDL_RenderDrawLine(mRenderer->GetRenderer(), 0, 0, SCREEN_WIDTH, 0);                                     // Line from top-left to top-right
        // SDL_RenderDrawLine(mRenderer->GetRenderer(), SCREEN_WIDTH - 1, 0, SCREEN_WIDTH, SCREEN_HEIGHT);          // Line from top-right to bottom-right
        // SDL_RenderDrawLine(mRenderer->GetRenderer(), SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, SCREEN_HEIGHT - 1); // Line from bottom-right to bottom-left
#pragma endregion

        int score = mPlayer->GetScore();
        int lives = mPlayer->GetLives();
        textRenderer->renderText(std::to_string(score).c_str(), 10, 10, textColor);
        textRenderer->renderText(std::to_string(lives).c_str(), SCREEN_WIDTH / 2, 10, textColor);

#pragma region Debug printing
        if (mIsDebug)
        {
            std::string dtstr = "dt: " + std::to_string(pDeltaTime);
            textRenderer->renderText(dtstr.c_str(), 50, 50, textColor);

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

            std::string count = "count: " + std::to_string(mProjectiles.size());
            textRenderer->renderText(count.c_str(), 50, 250, textColor);

            if (mAsteroids.size() > 0)
            {
                int exp = mAsteroids[indexer]->GetLives();

                std::string t3 = "lives: " + std::to_string(exp);
                textRenderer->renderText(t3.c_str(), 50, 300, textColor);

                float timer = mAsteroids[indexer]->GetScale();
                std::string t4 = "scale: " + std::to_string(timer);
                textRenderer->renderText(t4.c_str(), 50, 350, textColor);
            }
            std::string indexerer = "index: " + std::to_string(indexer);
            textRenderer->renderText(indexerer.c_str(), 50, 400, textColor);
        }
#pragma endregion

        // Cleanup unused projectiles
        for (size_t i = mProjectiles.size(); i-- > 0;)
        {
            if (mProjectiles[i]->GetHasExpired())
            {
                if (--indexer == -1)
                    indexer = 0;
                Projectile *tempProj = mProjectiles[i];
                mProjectiles.erase(mProjectiles.begin() + i);
                delete tempProj;
                mPlayer->SetShotProjectiles(mPlayer->GetShotProjectiles() - 1);
            }
        }

        for (size_t i = mAsteroids.size(); i-- > 0;)
        {
            if (mAsteroids[i]->GetHasExpired())
            {
                Asteroid *tempAsteroid = mAsteroids[i];
                mAsteroids.erase(mAsteroids.begin() + i);
                delete tempAsteroid;
            }
        }
    }
    mRenderer->EndRender();
}

void App::CheckCollisions()
{
    SDL_Color textColor = {255, 255, 255};
    std::vector<Asteroid *> tempAsteroids;

    for (auto &proj : mProjectiles)
    {
        for (auto &asteroid : mAsteroids)
        {
            Vector2f difference = proj->GetPos() - asteroid->GetPos();
            float distance = difference.Length();

            if (distance < proj->GetColliderRadius() + asteroid->GetColliderRadius())
            {
                if (asteroid->GetLives() > 1)
                {
                    for (size_t i = 0; i < 2; i++)
                    {
                        Asteroid *ast = new Asteroid;
                        ast->SetScale(asteroid->GetScale() - 0.25f);
                        ast->SetColliderRadius(asteroid->GetColliderRadius() * asteroid->GetScale());
                        ast->SetPosition(asteroid->GetPos());
                        ast->SetLives(asteroid->GetLives() - 1);
                        tempAsteroids.push_back(ast);
                    }
                }
                proj->OnCollision();
                asteroid->OnCollision();

                mPlayer->SetScore(mPlayer->GetScore() + 10);
            }
        }
    }

    for (size_t i = 0; i < tempAsteroids.size(); i++)
    {
        mAsteroids.push_back(tempAsteroids[i]);
    }

    for (auto &asteroid : mAsteroids)
    {
        // get distance between player and asteroid
        Vector2f difference = mPlayer->GetPos() - asteroid->GetPos();
        float distance = difference.Length();

        if (distance < mPlayer->GetColliderRadius() + asteroid->GetColliderRadius())
        {
            mPlayer->OnCollision();
            // clean up asteroids
            for (auto &asteroid : mAsteroids)
            {
                delete asteroid;
            }
            mAsteroids.clear();
            for (auto &proj : mProjectiles)
            {
                delete proj;
            }
            mProjectiles.clear();

            // reset to normal
            CreateAsteroids();
        }
    }
}

App::~App()
{
    for (auto &asteroid : mAsteroids)
    {
        delete asteroid;
    }
    for (auto &proj : mProjectiles)
    {
        delete proj;
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