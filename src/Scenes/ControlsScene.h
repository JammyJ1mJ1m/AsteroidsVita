#pragma once
#include "Scene.h"


class ControlsScene final : public Scene
{
	float mElapsed;
	float mTimeToSpawn;


	public:
	ControlsScene();
	virtual ~ControlsScene();
	virtual void Initialise();
	virtual void OnKeyboard(Button* pButton,SceCtrlData &padData);
	virtual void Update(double deltaTime);
	virtual void Render(Renderer* pRenderer, const float pDeltaTime);
};