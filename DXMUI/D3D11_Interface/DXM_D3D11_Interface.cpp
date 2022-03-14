#include "DXM_D3D11_Interface.h"
#include "DXMUIRenderSettings.h"
#include "Utility\DXMUI_Util.h"

#pragma comment(lib, "d3d11.lib")

using namespace DXMUI;
ID3D11Device* DXM_D3D11_Interface::myDevice;
HWND DXM_D3D11_Interface::ourHWND;

DXM_D3D11_Interface::DXM_D3D11_Interface()
{
	myDevice = nullptr;
	myDeviceContext = nullptr;
}

DXM_D3D11_Interface::~DXM_D3D11_Interface()
{
	ID3D11SamplerState* empty = nullptr;
	ID3D11Buffer* emptyBuffer = nullptr;
	myDeviceContext->PSSetSamplers(0, 1, &empty);
	myDeviceContext->OMSetBlendState(nullptr,0, 0xffffffff);
	myDeviceContext->GSSetConstantBuffers(0,1, &emptyBuffer);
	DXM_SafeRelease(&myDevice);
	DXM_SafeRelease(&myDeviceContext);
	DXMUIRenderSettings::Destroy();
}

bool DXM_D3D11_Interface::Init(HWND aWindow, ID3D11Device* aDevice, ID3D11DeviceContext* aContext)
{
	if (!aDevice)
		return false;
	if (!aContext)
		return false;

	myDevice = aDevice;
	myDeviceContext = aContext;
	ourHWND = aWindow;

	if (!DXMUIRenderSettings::Init(myDevice)) 
		return false; 

	if (!myRenderer.Init(myDevice))
		return false;

	return true;
}

void DXMUI::DXM_D3D11_Interface::RenderCanvas(Canvas& aCanvas)
{
	aCanvas.Render();
	myRenderer.Render(myDeviceContext);
	//TODO -> Cool rendering
}

ID3D11Device* DXMUI::DXM_D3D11_Interface::GetDevice()
{
	return myDevice;
}
