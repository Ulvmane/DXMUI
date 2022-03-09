#include "DXM_D3D11_Interface.h"

#pragma comment(lib, "d3d11.lib")
#include <d3d11.h>

using namespace DXMUI;

DXM_D3D11_Interface::DXM_D3D11_Interface()
{
	mySwapChain = nullptr;
	myDevice = nullptr;
	myDeviceContext = nullptr;
	myBackBuffer = nullptr;
}

DXM_D3D11_Interface::~DXM_D3D11_Interface()
{
	mySwapChain = nullptr;
	myDevice = nullptr;
	myDeviceContext = nullptr;
	myBackBuffer = nullptr;
}

bool DXM_D3D11_Interface::Init(HWND aHWND)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = aHWND;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;

	result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
										   nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
										   &swapChainDesc, &mySwapChain, &myDevice, nullptr, &myDeviceContext);

	if (FAILED(result)) {return false; }

	ID3D11Texture2D* backBufferTexture;
	result = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);
	if (FAILED(result)) {return false; }

	result = myDevice->CreateRenderTargetView(backBufferTexture, nullptr, &myBackBuffer);
	if (FAILED(result)) {return false; }

	result = backBufferTexture->Release();
	if (FAILED(result)) {return false; }

	return true;
}

void DXMUI::DXM_D3D11_Interface::RenderCanvas(Canvas& aCanvas)
{
	aCanvas.Render();
	//TODO -> Cool rendering
}
