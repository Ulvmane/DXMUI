#include "ImageElement.h"

#include "D3D11_Interface\DXMRenderer.h"

#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include "Utility\DXMUI_Util.h"

#include "D3D11_Interface\DXM_D3D11_Interface.h"

#include "Parser\Styles\DXUIStyle.h"
#include <assert.h>

DXMUI::ImageElement::ImageElement(const char* aPath)
{
	myPath = aPath;
	std::wstring wPath = std::wstring(myPath.begin(), myPath.end());

#undef _XM_NO_INTRINSICS_

	HRESULT result = S_FALSE;
	result = DirectX::CreateDDSTextureFromFile(DXM_D3D11_Interface::GetDevice(),wPath.c_str(),0, &myTexture);
	if (FAILED(result))
	{
		result = DirectX::CreateWICTextureFromFile(DXM_D3D11_Interface::GetDevice(), wPath.c_str(), 0, &myTexture);
	}

	if (SUCCEEDED(result))
	{
		ID3D11Texture2D* pTextureInterface = 0;
		ID3D11Resource* resource;
		myTexture->GetResource(&resource);
		resource->QueryInterface<ID3D11Texture2D>(&pTextureInterface);
		D3D11_TEXTURE2D_DESC textureDesc;
		pTextureInterface->GetDesc(&textureDesc);

		auto clientRect = RECT();
		GetClientRect(DXM_D3D11_Interface::GetHWND(), &clientRect);
		auto scaleX = float{ textureDesc.Width  / static_cast<float>(clientRect.right - clientRect.left)};
		auto scaleY = float{ textureDesc.Height / static_cast<float>(clientRect.bottom - clientRect.top)};

		myHeight = scaleY;
		myWidth = scaleX;

		mySurface.myElementBufferData.myColor = Color{ 1,1,1,1 };
		mySurface.myElementBufferData.myPivot = Vector2{ 0.f,0.f };
		mySurface.myElementBufferData.myPosition = Vector2{ 0.5f, 0.5f };
		mySurface.myElementBufferData.mySize = Vector2{ scaleX,scaleY };
		mySurface.myElementBufferData.myTextureRect = TextureRect{ 0,0,1,1 };
		mySurface.myElementBufferData.myHasTexture = true;
		mySurface.myTexture.myWriteToGPU = true;
		mySurface.myTexture.myTexture = myTexture;

		DXM_SafeRelease(&pTextureInterface);
		DXM_SafeRelease(&resource);
	}
}

DXMUI::ImageElement::~ImageElement()
{
	DXM_SafeRelease(&myTexture);
}

void DXMUI::ImageElement::Render()
{
	DXMRenderer::AddDrawSurface(mySurface);
}

void DXMUI::ImageElement::SetPosition(const float aX, const float aY)
{
	mySurface.myElementBufferData.myPosition = Vector2{ aX, aY };
}

DXMUI::Vector2 DXMUI::ImageElement::GetPosition()
{
	return mySurface.myElementBufferData.myPosition;
}

void DXMUI::ImageElement::SetStyle(const DXUIStyle& aStyle)
{
	mySurface.myElementBufferData.myColor = aStyle.myColor;
	mySurface.myElementBufferData.mySize.x *= aStyle.mySize.x;
	mySurface.myElementBufferData.mySize.y *= aStyle.mySize.y;
	myWidth *= aStyle.mySize.x;
	myHeight *= aStyle.mySize.y;


	myBorder = aStyle.myBorder;
	myPadding = aStyle.myPadding;
	myMargin = aStyle.myMargin;
}
