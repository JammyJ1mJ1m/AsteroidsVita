#include "SceneManager.h"
#include  "../Scenes/Scene.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

SceneManager::SceneManager(App* pGame)
	: mGame(pGame)
{
}


SceneManager::~SceneManager()
{
}


void SceneManager::OnKeyboard(Button* pButton,SceCtrlData &padData)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene)
	{
		currentScene->OnKeyboard(pButton, padData);
	}
}

void SceneManager::Update(double pDeltaTime)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene)
	{
		currentScene->Update(pDeltaTime);
	}
}

// Render current scene
void SceneManager::Render(Renderer* pRenderer, const float pDeltaTime)
{
	Scene* currentScene = GetCurrentScene();
	if (currentScene)
	{
		currentScene->Render(pRenderer,pDeltaTime);
	}
}

void SceneManager::PushScene(Scene* pScene)
{
	mScenes.push(pScene);
	pScene->SetSceneManager(this);
	pScene->Initialise();
}