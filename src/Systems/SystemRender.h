#pragma once
#include "ISystem.h"
#include "../Renderer.h"



// master render system will handle and call relevant classes, forward, deferred UI etc
class SystemRender : public ISystem
{
	//IComponent::ComponentTypes mMask;
	Renderer* mRenderer;


public:
	SystemRender(Renderer* pRenderer);
	~SystemRender();
	virtual void Run(Model* pEntity);
	void Render(std::vector<Model*>& pEntities);
	
	//void DrawPP();
	void Begin();
	void End();
	void PostProcess();

};