#include "DivElement.h"
#include <iostream>
#include "D3D11_Interface\DXMRenderer.h"
#include "Parser\Styles\DXUIStyle.h"

DXMUI::DivElement::DivElement()
{
	mySurface.myElementBufferData.myColor = Color{ 0,0,0,0 };
	mySurface.myElementBufferData.myPivot = Vector2{ 0.f,0.f };
	mySurface.myElementBufferData.myPosition = Vector2{ 0.5f, 0.5f };
	mySurface.myElementBufferData.mySize = Vector2{ myHeight,1 };
	mySurface.myElementBufferData.myTextureRect = TextureRect{ 0,0,1,1 };
	mySurface.myElementBufferData.myHasTexture = false;
	mySurface.myTexture = Texture{ false, nullptr };
}

void DXMUI::DivElement::Render()
{
	DXMRenderer::AddDrawSurface(mySurface);
}

void DXMUI::DivElement::SetPosition(const float aX, const float aY)
{
	mySurface.myElementBufferData.myPosition = Vector2{ aX , aY};

}

DXMUI::Vector2 DXMUI::DivElement::GetPosition()
{
	return mySurface.myElementBufferData.myPosition;
}

void DXMUI::DivElement::SetHeight(const float aHeight)
{
	myHeight = aHeight;
	mySurface.myElementBufferData.mySize = Vector2{ 1, myHeight };
}

void DXMUI::DivElement::SetStyle(const DXUIStyle& aStyle)
{
	mySurface.myElementBufferData.myColor = aStyle.myColor;


	myBorder = aStyle.myBorder;
	myPadding = aStyle.myPadding;
	myMargin = aStyle.myMargin;
}
