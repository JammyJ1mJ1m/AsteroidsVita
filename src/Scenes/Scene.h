#pragma once
#include <vector>
#include "../Model.h"

class SystemRender;

class SceneManager;
class Renderer;
class Button;
class SceCtrlData;

/// Represents an abstract scene, i.e. mode of the game
/// For example, MainMenu, Gameplay, GameOver etc
class Scene
{
protected:
	SceneManager* mSceneManager;
	std::vector<Model*> mEntities;

public:
	Scene();
	virtual ~Scene();

	std::vector<Model*>& GetEntities() { return mEntities; }
	void AddEntity(Model* obj) { mEntities.push_back(obj); }

	int GetEntityCount() const { return mEntities.size(); }

	void SetSceneManager(SceneManager* s) { mSceneManager = s; }
	SceneManager* GetSceneManager()	const { return mSceneManager; }

	virtual void Initialise() = 0;

	virtual void OnKeyboard(Button* pButton,SceCtrlData &padData) = 0;

	virtual void Update(double deltaTime) = 0;

	virtual void Render(Renderer* pRenderer, const float pDeltaTime) = 0;
};