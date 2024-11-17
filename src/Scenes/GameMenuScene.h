#pragma once
#include "Scene.h"
#include "../TextRenderer.h"


class GameMenuScene final : public Scene
{
	float mElapsed;
	float mTimeToSpawn;
    TextRenderer *textRenderer;
	int UIIndex;
	int UIItems;


	public:
	GameMenuScene();
	virtual ~GameMenuScene();
	virtual void Initialise();
	virtual void OnKeyboard(Button* pButton,SceCtrlData &padData);
	virtual void Update(double deltaTime);
	virtual void Render(Renderer* pRenderer, const float pDeltaTime);
};