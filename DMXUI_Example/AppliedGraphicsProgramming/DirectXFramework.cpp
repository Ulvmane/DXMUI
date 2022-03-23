#include "DirectXFramework.h"
#include "WindowHandler.h"
#include <d3d11.h>
#include "Utility\DXMUI_Util.h"

CDirectX11Framework::CDirectX11Framework()
{
	mySwapChain		= nullptr;
	myDevice		= nullptr;
	myDeviceContext = nullptr;
	myBackBuffer	= nullptr;
}

CDirectX11Framework::~CDirectX11Framework()
{
	mySwapChain->SetFullscreenState(false, NULL);
	DXM_SafeRelease(&mySwapChain);
	DXM_SafeRelease(&myBackBuffer);
}

void CDirectX11Framework::BeginFrame(std::array<float, 4> aClearColor)
{
	myDeviceContext->ClearRenderTargetView(myBackBuffer, &aClearColor[0]);
}

void CDirectX11Framework::EndFrame()
{
	mySwapChain->Present(1,0);
}

bool CDirectX11Framework::Init(CWindowHandler* aWindowHandler)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = aWindowHandler->GetWindowHandle();
	swapChainDesc.SampleDesc.Count = 2;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;

	result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
										   nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
										   &swapChainDesc, &mySwapChain, &myDevice, nullptr, &myDeviceContext);

	if (FAILED(result)) {/*Print fail info*/ return false; }

	ID3D11Texture2D* backBufferTexture;
	result = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);
	if (FAILED(result)) {/*Print fail info*/ return false; }

	result = myDevice->CreateRenderTargetView(backBufferTexture, nullptr, &myBackBuffer);
	if (FAILED(result)) {/*Print fail info*/ return false; }

	result = backBufferTexture->Release();
	if (FAILED(result)) {/*Print fail info*/ return false; }

	myDeviceContext->OMSetRenderTargets(1, &myBackBuffer, nullptr);
	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(aWindowHandler->GetWidth());
	viewport.Height = static_cast<float>(aWindowHandler->GetHeight());
	viewport.MinDepth = 0.f;
	viewport.MaxDepth = 1.0f;
	myDeviceContext->RSSetViewports(1, &viewport);


	return true;
}
