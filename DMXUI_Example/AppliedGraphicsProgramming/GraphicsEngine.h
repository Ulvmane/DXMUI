#pragma once
#include "WindowHandler.h"
#include "DirectXFramework.h"

class CGraphicsEngine
{
public:
	bool Init(CWindowHandler::SWindowData& aWindowData);

	void BeginFrame();
	void EndFrame();
private:
	
	CWindowHandler		myWindowHandler;
	CDirectX11Framework myFrameWork;
};

