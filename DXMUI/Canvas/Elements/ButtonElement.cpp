#include "ButtonElement.h"
#include "D3D11_Interface\DXMRenderer.h"
#include "D3D11_Interface\DXMTextRenderer.h"
#include "D3D11_Interface\DXM_D3D11_Interface.h"
#include "Parser\Styles\DXUIStyle.h"

DXMUI::ButtonElement::ButtonElement(const char* aText)
{
	auto data = std::string(aText);

	myRenderText.myPosition = Vector2{ 0,0 };
	myRenderText.myRotation = 0;
	myRenderText.myScale = Vector2{ 1,1 };
	myRenderText.myText = std::wstring(data.begin(), data.end());

	auto spriteFont = DXMTextRenderer::GetDefaultSpriteFont();

	auto dimension = (spriteFont->MeasureString(myRenderText.myText.c_str()));

	myWidth = (DirectX::XMVectorGetX(dimension))  / ourReferenceWidth;
	myHeight = (DirectX::XMVectorGetY(dimension)) / ourReferenceHeight;
	myRenderText.myOrigin = { 0.f, 0.f};
	
    myFontOffset = GetFontOffset(spriteFont, myRenderText.myText);


	mySurface.myElementBufferData.myHasTexture = false;
	mySurface.myElementBufferData.myColor = Color{ 0,0,0,0.5f };
	mySurface.myElementBufferData.myPivot = Vector2{ -0.f,0.f };
	mySurface.myElementBufferData.mySize = Vector2{ myWidth, myHeight };
	mySurface.myElementBufferData.myTextureRect = TextureRect{ 0,0,1,1 };
	mySurface.myElementBufferData.myPosition = Vector2{ 0,0 };
}

void DXMUI::ButtonElement::Render()
{
	DXMRenderer::AddDrawSurface(mySurface);
	DXMTextRenderer::AddText(myRenderText);
}

void DXMUI::ButtonElement::SetPosition(const float aX, const float aY)
{
	auto adjustedPosition = AdjustByAlignmentAndPivot({ aX, aY }, myAlignment, myPivot, {myWidth, myHeight});
	auto pivotAlignAdjustedX = adjustedPosition.x - myPivot.x * myWidth;
	auto pivotAlignAdjustedY = adjustedPosition.y - myPivot.y * myHeight;
	mySurface.myElementBufferData.myPosition = {pivotAlignAdjustedX - myPadding.left, pivotAlignAdjustedY + myMargin.top};
	myRenderText.myPosition = Vector2{ adjustedPosition.x * ourReferenceWidth, (myPadding.top + adjustedPosition.y) * ourReferenceHeight  };
	myRenderText.myPosition.x -= 0.5f * myFontOffset.x * ourReferenceWidth;
	myRenderText.myOrigin.x = ourReferenceWidth * myWidth * myPivot.x;
}

DXMUI::Vector2 DXMUI::ButtonElement::GetPosition()
{
	return mySurface.myElementBufferData.myPosition;
}

void DXMUI::ButtonElement::SetStyle(const DXUIStyle& aStyle)
{
	mySurface.myElementBufferData.myColor = aStyle.myColor;
	myWidth *= aStyle.mySize.x;
	myHeight *= aStyle.mySize.y;
	myRenderText.myScale = aStyle.mySize;
	mySurface.myElementBufferData.mySize = { myWidth, myHeight };
	myAlignment = aStyle.myAlignment;
	myPivot = aStyle.myPivot;


	myBorder  = aStyle.myBorder;
	myPadding = aStyle.myPadding;
	myMargin  = aStyle.myMargin;
	
	mySurface.myElementBufferData.mySize.x += myPadding.left + myPadding.right;
	mySurface.myElementBufferData.mySize.y += myPadding.top + myPadding.bottom;
}
