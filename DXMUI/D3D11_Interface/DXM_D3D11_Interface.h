#pragma once
#include <array>
#include "Canvas\Canvas.h"
#include <Windows.h>

class IDXGISwapChain;
class ID3D11Device;
class ID3D11DeviceContext;
class ID3D11RenderTargetView;

namespace DXMUI
{
	class CWindowHandler;

	class DXM_D3D11_Interface
	{
	public:
		DXM_D3D11_Interface();
		~DXM_D3D11_Interface();
		bool Init(HWND aHWND);
		void RenderCanvas(Canvas& aCanvas);
	private:
		IDXGISwapChain* mySwapChain;
		ID3D11Device* myDevice;
		ID3D11DeviceContext* myDeviceContext;
		ID3D11RenderTargetView* myBackBuffer;

	};
}

