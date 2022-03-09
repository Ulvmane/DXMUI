#pragma once
#include <array>

class IDXGISwapChain;
class ID3D11Device;
class ID3D11DeviceContext;
class ID3D11RenderTargetView;

class CWindowHandler;

class CDirectX11Framework
{
public:
	CDirectX11Framework();
	~CDirectX11Framework();
	void Render();
	void EndFrame();
private:
	IDXGISwapChain*			mySwapChain;
	ID3D11Device*			myDevice;
	ID3D11DeviceContext*	myDeviceContext;
	ID3D11RenderTargetView* myBackBuffer;
};

