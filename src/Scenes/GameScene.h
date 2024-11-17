#pragma once
#include "Scene.h"
#include <vector>
#include "../Asteroid.h"
#include "../Projectile.h"
#include "../Player.h"

struct Star
{
    Vector2f pos;
    Vector3f col;
};

class GameScene final : public Scene
{
	float mElapsed;
	float mTimeToSpawn;
    bool mIsDebug;
    std::vector<Asteroid *> mAsteroids;

    std::vector<Projectile *> mProjectiles;
    int indexer;
    std::vector<Star> mBGStars;
    Player *mPlayer;
	int mAsteroidLevel;



	public:
    void CreateAsteroids(const int pAstCount);

	GameScene();
	virtual ~GameScene();
	virtual void Initialise();
	virtual void OnKeyboard(Button* pButton,SceCtrlData &padData);
	virtual void Update(double deltaTime);
	virtual void Render(Renderer* pRenderer, const float pDeltaTime);
    void CheckCollisions();

};