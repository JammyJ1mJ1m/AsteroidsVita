#pragma once
#include <stack>
#include <vector>
#include "../Button.h"

class Renderer;
class Scene;
class App;

/// Handles the Scenes for a game
class SceneManager
{
	// Constants
public:

	// Data
protected:
	App* mGame;
	std::stack<Scene*>	mScenes;

	// Structors
public:
	SceneManager(App* pGame);
	~SceneManager();


	// Gets/Sets
public:
	Scene* GetCurrentScene()	const { if (mScenes.size() > 0) return mScenes.top(); else return NULL; }
	App* GetGame()				const { return mGame; }

	// Functions
public:

	/// Respond to input
	void OnKeyboard(Button* pButton,SceCtrlData &padData);

	/// Update current scene
	void Update(double pDeltaTime);

	/// Render current scene
	void Render(Renderer* pRenderer, const float pDeltaTime);

	/// Pop the top scene. If no scenes remain, we should quit.
	void PopScene() { mScenes.pop(); }

	/// Push a new scene
	void PushScene(Scene* pScene);
};