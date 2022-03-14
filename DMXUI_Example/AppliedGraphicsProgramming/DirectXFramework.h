#pragma once
#include <array>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

class CWindowHandler;

class CDirectX11Framework
{
public:
	CDirectX11Framework();
	~CDirectX11Framework();
	void EndFrame();
	bool Init(CWindowHandler* aHWND);
	void BeginFrame(std::array<float, 4> aClearColor);
	ID3D11Device* myDevice;
	ID3D11DeviceContext* myDeviceContext;
private:
	IDXGISwapChain*			mySwapChain;
	ID3D11RenderTargetView* myBackBuffer;
};

