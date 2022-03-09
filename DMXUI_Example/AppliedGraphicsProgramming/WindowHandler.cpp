#include "WindowHandler.h"

LRESULT CALLBACK CWindowHandler::WinProc(HWND aHWND, UINT aUMsg, WPARAM aWParam, LPARAM aLParam)
{
	static CWindowHandler* windowHandler = nullptr;

	if (aUMsg == WM_DESTROY || aUMsg == WM_CLOSE)
	{
		PostQuitMessage(0);
		return 0;
	}
	else if (aUMsg == WM_CREATE)
	{
		CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(aLParam);
		windowHandler = reinterpret_cast<CWindowHandler*>(createStruct->lpCreateParams);
	}
	return DefWindowProc(aHWND, aUMsg, aWParam, aLParam);
}

bool CWindowHandler::Init(const SWindowData& aWindowData)
{
	WNDCLASS windowClass = {};
	windowClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = CWindowHandler::WinProc;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszClassName = L"Applied Graphics Programming";
	RegisterClass(&windowClass);

	myWindowHandle = CreateWindow(L"Applied Graphics Programming", L"My Game",
								  WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE,
								  aWindowData.myX, aWindowData.myY, aWindowData.myWidth, aWindowData.myHeight,
								  nullptr, nullptr, nullptr, this);

	return true;
}

HWND& CWindowHandler::GetWindowHandle()
{
	return myWindowHandle;
}
