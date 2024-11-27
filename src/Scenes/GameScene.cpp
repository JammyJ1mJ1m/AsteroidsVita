#include "GameScene.h"

#include <sstream>
#include "../Renderer.h"
#include "../App.h"
#include "GameOverScene.h"
// #include <chrono>

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	for (auto &asteroid : mAsteroids)
	{
		delete asteroid;
	}
	for (auto &proj : mProjectiles)
	{
		delete proj;
	}
}

/// <summary>
/// All game objects are created here and members are initialised
/// </summary>
void GameScene::Initialise()
{
	mIsDebug = false;
	mPlayer = App::GetApp()->GetPlayer();

	indexer = 0;

	mAsteroidLevel = 4;
	CreateAsteroids(mAsteroidLevel);

	float starCount = 50;
	for (size_t i = 0; i < starCount; i++)
	{
		Star star;
		star.pos = Vector2f(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
		star.col = Vector3f(25 + (rand() % 180), 25 + (rand() % 180), 25 + (rand() % 180), 255);
		mBGStars.push_back(star);

		/* code */
	}
}

void GameScene::OnKeyboard(Button *pButton, SceCtrlData &padData)
{
	if (pButton->GetKey() == SCE_CTRL_R1 && pButton->CheckKey(padData))
	{
		// move logic
		mPlayer->SetSpeed(1);
	}
	if (pButton->GetKey() == SCE_CTRL_SQUARE && pButton->CheckButtonDown(padData))
	{
		if (mPlayer->GetShotProjectiles() >= 5)
			return;

		Projectile *proj = mPlayer->ShootProjectile();

		proj->SetPosition(mPlayer->GetPos());
		proj->SetRotation(mPlayer->GetRotation());
		proj->UpdateVelocity(10);
		mProjectiles.push_back(proj);
	}

	if (pButton->GetKey() == SCE_CTRL_LEFT && pButton->CheckKey(padData))
	{
		mPlayer->SetRotation(mPlayer->GetRotation() - 3);
	}
	if (pButton->GetKey() == SCE_CTRL_RIGHT && pButton->CheckKey(padData))
	{
		mPlayer->SetRotation(mPlayer->GetRotation() + 3);
	}
}

void GameScene::Update(double deltaTime)
{
	mPlayer->Update(deltaTime);

	for (auto &asteroid : mAsteroids)
	{
		asteroid->Update(deltaTime);
	}
	for (auto &proj : mProjectiles)
	{
		if (proj->GetCurrentLifeTime() >= proj->GetMaxLifeTime())
		{
			proj->SetHasExpired(true);
			continue;
		}
		proj->Update(deltaTime);
	}
	CheckCollisions();

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

	// pRenderer->EndRender();
	if (mAsteroids.size() == 0)
	{
		CreateAsteroids(mAsteroidLevel++);
	}
	if (mPlayer->GetHasExpired())
	{
		mSceneManager->PopScene();
		mSceneManager->PushScene(new GameOverScene());
		mPlayer->ResetPlayer();
	}
}

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

void GameScene::CreateAsteroids(const int pAstCount)
{
	for (size_t i = 0; i < pAstCount; i++)
	{
		mAsteroids.push_back(new Asteroid());
	}
}

void GameScene::Render(Renderer *pRenderer, const float pDeltaTime)
{
	TextRenderer *textRenderer = App::GetApp()->GetTextRenderer();

	SDL_Color textColor = {255, 255, 255};

#pragma region Main rendering

	mPlayer->Draw(pRenderer);
	if (mIsDebug)
		DrawCircle(pRenderer->GetRenderer(), mPlayer->GetPos().GetX(), mPlayer->GetPos().GetY(), mPlayer->GetColliderRadius());

	for (size_t i = 0; i < mAsteroids.size(); i++)
	// for (auto &asteroid : mAsteroids)
	{
		SDL_SetRenderDrawColor(pRenderer->GetRenderer(), 255, 0, 0, 255);
		if (i == indexer)
			SDL_SetRenderDrawColor(pRenderer->GetRenderer(), 255, 0, 255, 255);
		if (mIsDebug)
			DrawCircle(pRenderer->GetRenderer(), mAsteroids[i]->GetPos().GetX(), mAsteroids[i]->GetPos().GetY(), mAsteroids[i]->GetColliderRadius());

		mAsteroids[i]->Draw(pRenderer);
	}

	for (auto &proj : mProjectiles)
	{
		SDL_SetRenderDrawColor(pRenderer->GetRenderer(), 255, 0, 0, 255);
		if (mIsDebug)
			DrawCircle(pRenderer->GetRenderer(), proj->GetPos().GetX(), proj->GetPos().GetY(), proj->GetColliderRadius());

		proj->Draw(pRenderer);
	}

	for (auto &star : mBGStars)
	{
		SDL_SetRenderDrawColor(pRenderer->GetRenderer(), star.col.GetX(), star.col.GetY(), star.col.GetZ(), 1);
		SDL_RenderDrawPoint(pRenderer->GetRenderer(), star.pos.GetX(), star.pos.GetY());
	}

#pragma endregion

#pragma region Boundary drawing
	// SDL_SetRenderDrawColor(pRenderer->GetRenderer(), 255, 0, 0, 255);
	// SDL_RenderDrawLine(pRenderer->GetRenderer(), 0, SCREEN_HEIGHT, 0, 0);                                    // Line from bottom-left to top-left
	// SDL_RenderDrawLine(pRenderer->GetRenderer(), 0, 0, SCREEN_WIDTH, 0);                                     // Line from top-left to top-right
	// SDL_RenderDrawLine(pRenderer->GetRenderer(), SCREEN_WIDTH - 1, 0, SCREEN_WIDTH, SCREEN_HEIGHT);          // Line from top-right to bottom-right
	// SDL_RenderDrawLine(pRenderer->GetRenderer(), SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, SCREEN_HEIGHT - 1); // Line from bottom-right to bottom-left
#pragma endregion


	textRenderer->renderText(std::to_string(mPlayer->GetScore()).c_str(), 10, 10, textColor);
	textRenderer->renderText(std::to_string(mPlayer->GetLives()).c_str(), SCREEN_WIDTH / 2, 10, textColor);
}

void GameScene::CheckCollisions()
{
	SDL_Color textColor = {255, 255, 255};
	std::vector<Asteroid *> tempAsteroids;

	for (auto &proj : mProjectiles)
	{
		for (auto &asteroid : mAsteroids)
		{
			Vector2f difference = proj->GetPos() - asteroid->GetPos();
			float distance = difference.Length();

			if (distance > proj->GetColliderRadius() + asteroid->GetColliderRadius())
				continue; // No collisions happening, iterate to next set

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

			// first - 20
			// second - 50
			// third  -100
			switch (asteroid->GetLives())
			{
			case 2:
				mPlayer->SetScore(mPlayer->GetScore() + 50);
				/* code */
				break;
			case 1:
				mPlayer->SetScore(mPlayer->GetScore() + 100);

				/* code */
				break;

			default:
				mPlayer->SetScore(mPlayer->GetScore() + 20);

				break;
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
			CreateAsteroids(mAsteroidLevel);
		}
	}
}