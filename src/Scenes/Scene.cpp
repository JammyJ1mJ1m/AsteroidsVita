#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (size_t i = 0; i < mEntities.size(); i++)
	{
		delete mEntities[i];
	}
	mEntities.clear();
}