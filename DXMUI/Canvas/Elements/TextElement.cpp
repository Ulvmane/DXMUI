#include "TextElement.h"
#include "D3D11_Interface\DXMTextRenderer.h"
#include "D3D11_Interface\DXM_D3D11_Interface.h"
#include "Parser\Styles\DXUIStyle.h"
#include "Utility\FontHandler.h"


DXMUI::TextElement::TextElement(const char* aInData)
{
	auto data = std::string(aInData);
	myRenderText.myPosition = Vector2{ 0,0 };
	myRenderText.myRotation = 0;
	myRenderText.myScale = Vector2{ 1,1 };
	myRenderText.myText = std::wstring(data.begin(), data.end());
	myRenderText.myOrigin = { 0.f, 0.f};

	auto spriteFont = DXMTextRenderer::GetDefaultSpriteFont();

	auto drawRect = spriteFont->MeasureDrawBounds(myRenderText.myText.c_str(), DirectX::XMFLOAT2(0.f, 0.f), true);
	myFontOffset= GetFontOffset(spriteFont,myRenderText.myText);

	auto dimension = (spriteFont->MeasureString(myRenderText.myText.c_str(), false));

	myWidth  = ((DirectX::XMVectorGetX(dimension)) - drawRect.left) / ourReferenceWidth;
	myHeight = (DirectX::XMVectorGetY(dimension)) / ourReferenceHeight;
}

void DXMUI::TextElement::Render()
{
	DXMTextRenderer::AddText(myRenderText);


	//auto bg = DXMDrawSurface();
	//bg.myElementBufferData.myColor = { 1,0,0,1 };
	//bg.myElementBufferData.myHasTexture = false;
	//bg.myElementBufferData.myTextureRect = { 0,0,1,1 };
	//bg.myElementBufferData.myPivot = myPivot;
	//bg.myElementBufferData.myPosition = myScreenSpacePosition;
	//bg.myElementBufferData.myPosition.x -= 0;
	//bg.myElementBufferData.mySize = { myWidth,myHeight };

	//DXMRenderer::AddDrawSurface(bg);
	
}

void DXMUI::TextElement::SetPosition(const float aX, const float aY)
{
	auto clientRect = RECT();
	GetClientRect(DXM_D3D11_Interface::GetHWND(), &clientRect);

	auto adjustedPosition = AdjustByAlignmentAndPivot({ aX, aY }, myAlignment, {0,0}, { myWidth, myHeight });

	myRenderText.myOrigin.x = ourReferenceWidth * myWidth * myPivot.x + (myWidth * ourReferenceWidth * (1 - myScale.x));
	myRenderText.myPosition = Vector2{ (adjustedPosition.x) * ourReferenceWidth, (adjustedPosition.y + myPadding.top + myMargin.top) * ourReferenceHeight };
	myRenderText.myPosition.x -= myFontOffset.x * ourReferenceWidth;
	myScreenSpacePosition	= adjustedPosition;
}

DXMUI::Vector2 DXMUI::TextElement::GetPosition()
{
	return myScreenSpacePosition;
}

void DXMUI::TextElement::SetStyle(const DXUIStyle& aStyle)
{
	myRenderText.myColor = aStyle.myColor;
	myRenderText.myScale = aStyle.mySize;
	myRenderText.myFont = aStyle.myFont;
	myAlignment = aStyle.myAlignment;
	myPivot = aStyle.myPivot;
	myScale = aStyle.mySize;

	if (aStyle.myFont != "")
	{
		auto spriteFont = FontHandler::GetSpriteFont(aStyle.myFont);
		myFontOffset = GetFontOffset(spriteFont, myRenderText.myText);

		auto dimension = (spriteFont->MeasureString(myRenderText.myText.c_str(), false));
		myWidth = ((DirectX::XMVectorGetX(dimension))) / ourReferenceWidth;
		myWidth -= myFontOffset.x;
		myHeight = (DirectX::XMVectorGetY(dimension)) / ourReferenceHeight;
	}
	myHeight *= aStyle.mySize.y;
	myWidth *= aStyle.mySize.x;

	myBorder = aStyle.myBorder;
	myPadding = aStyle.myPadding;
	myMargin = aStyle.myMargin;
}
