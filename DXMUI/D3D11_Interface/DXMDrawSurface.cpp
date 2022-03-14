#include "DXMDrawSurface.h"
#include <d3d11.h>

DXMUI::DXMDrawSurface::DXMDrawSurface()
{
}

void DXMUI::DXMDrawSurface::Render(ID3D11DeviceContext* aContext)
{
	if (myTexture.myWriteToGPU)
	{
		aContext->PSSetShaderResources(0, 1, &myTexture.myTexture);
	}
	else
	{
		ID3D11ShaderResourceView* nullResource = nullptr;
		aContext->PSSetShaderResources(0, 1, &nullResource);
	}

	aContext->Draw(1, 0);
}

void DXMUI::DXMDrawSurface::SetTexture(std::wstring& aTexturePath)
{

}
