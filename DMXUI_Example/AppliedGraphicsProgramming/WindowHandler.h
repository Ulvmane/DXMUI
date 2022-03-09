#pragma once
#include <Windows.h>
class CWindowHandler
{
public:
	struct SWindowData
	{
		int myX;
		int myY;
		int myWidth;
		int myHeight;
	};
	static LRESULT CALLBACK WinProc(_In_ HWND aHWND, _In_ UINT aUMSg, _In_ WPARAM aWParam, _In_ LPARAM aLParam);
	bool Init(const SWindowData& aWindowData);
	HWND& GetWindowHandle();

private:
	HWND myWindowHandle;
};



