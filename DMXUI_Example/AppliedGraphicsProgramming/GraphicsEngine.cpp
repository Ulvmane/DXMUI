#include "GraphicsEngine.h"

bool CGraphicsEngine::Init(CWindowHandler::SWindowData& aWindowData)
{
	if (!myWindowHandler.Init(aWindowData))
	{
		return false;
	}

	if (!myFrameWork.Init(&myWindowHandler))
	{
		return false;
	}

	return true;
}

void CGraphicsEngine::BeginFrame()
{
	std::array<float, 4> clearColor = { 1,0,0,1 }; //Red clear
	myFrameWork.BeginFrame(clearColor);
}

void CGraphicsEngine::EndFrame()
{
	myFrameWork.EndFrame();
}
