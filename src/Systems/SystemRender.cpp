
#include "SystemRender.h"


SystemRender::SystemRender(Renderer* pRenderer)
{
	mRenderer = pRenderer;

}

SystemRender::~SystemRender()
{
}

void SystemRender::Run(Model* pEntity)
{}

void SystemRender::Render(std::vector<Model*>& pEntities)
{
	
}

void SystemRender::Begin()
{

}

void SystemRender::End()
{

}

void SystemRender::PostProcess()
{

}