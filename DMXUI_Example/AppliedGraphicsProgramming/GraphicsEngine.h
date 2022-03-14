#pragma once
#include "WindowHandler.h"
#include "DirectXFramework.h"

class CGraphicsEngine
{
public:
	~CGraphicsEngine() = default;
	bool Init(CWindowHandler::SWindowData& aWindowData);

	void BeginFrame();
	void EndFrame();
	HWND GetHWND() { return myWindowHandler.GetWindowHandle(); }
	__inline CDirectX11Framework& GetFramework() { return myFrameWork; }
private:
	
	CWindowHandler		myWindowHandler;
	CDirectX11Framework myFrameWork;
};

