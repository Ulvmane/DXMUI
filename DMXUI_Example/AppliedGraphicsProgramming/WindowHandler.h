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
	} myWindowData;
	static LRESULT CALLBACK WinProc(_In_ HWND aHWND, _In_ UINT aUMSg, _In_ WPARAM aWParam, _In_ LPARAM aLParam);
	bool Init(const SWindowData& aWindowData);
	HWND& GetWindowHandle();
	__forceinline float GetWidth() { return myWindowData.myWidth; }
	__forceinline float GetHeight() {return myWindowData.myHeight; }
private:
	HWND myWindowHandle;
};



