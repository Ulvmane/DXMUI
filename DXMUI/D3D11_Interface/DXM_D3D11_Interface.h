#pragma once
#include <array>
#include "Canvas\Canvas.h"
#include <Windows.h>
#include "DXMRenderer.h"

#include <d3d11.h>
//struct IDXGISwapChain;
//struct ID3D11Device;
//struct ID3D11DeviceContext;
//struct ID3D11RenderTargetView;

namespace DXMUI
{
	class CWindowHandler;

	class DXM_D3D11_Interface
	{
	public:
		DXM_D3D11_Interface();
		~DXM_D3D11_Interface();
		bool Init(HWND aWindow, ID3D11Device* aDevice, ID3D11DeviceContext* aContext);
		void RenderCanvas(Canvas& aCanvas);
		static ID3D11Device* GetDevice();
		static __forceinline HWND GetHWND() { return ourHWND; }
	private:
		static ID3D11Device* myDevice;
		static HWND ourHWND;
		ID3D11DeviceContext* myDeviceContext;
		DXMRenderer myRenderer;
	};
}

