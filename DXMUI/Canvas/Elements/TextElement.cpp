#include "TextElement.h"
#include "D3D11_Interface\DXMTextRenderer.h"
#include "D3D11_Interface\DXM_D3D11_Interface.h"
#include "Parser\Styles\DXUIStyle.h"

DXMUI::TextElement::TextElement(const char* aInData)
{
	auto data = std::string(aInData);
	myRenderText.myPosition = Vector2{ 0,0 };
	myRenderText.myRotation = 0;
	myRenderText.myScale = Vector2{ 1,1 };
	myRenderText.myText = std::wstring(data.begin(), data.end());
	myRenderText.myOrigin = { 0.f, 0.f};

	auto spriteFont = DXMTextRenderer::GetDefaultSpriteFont();
	spriteFont->SetDefaultCharacter(L' ');
	
	auto drawRect = spriteFont->MeasureDrawBounds(myRenderText.myText.c_str(), DirectX::XMFLOAT2(0.f, 0.f), true);
	auto clientRect = RECT();
	GetClientRect(DXM_D3D11_Interface::GetHWND(), &clientRect);
	myFontOffset.x = drawRect.left / static_cast<float>(clientRect.right - clientRect.left);

	auto dimension = (spriteFont->MeasureString(myRenderText.myText.c_str(), false));

	myWidth  = ((DirectX::XMVectorGetX(dimension)) - drawRect.left) / static_cast<float>(clientRect.right - clientRect.left);
	myHeight = (DirectX::XMVectorGetY(dimension)) / static_cast<float>(clientRect.bottom - clientRect.top);
}

void DXMUI::TextElement::Render()
{
	DXMTextRenderer::AddText(myRenderText);


	////auto bg = DXMDrawSurface();
	////bg.myElementBufferData.myColor = { 0,0,0,1 };
	////bg.myElementBufferData.myHasTexture = false;
	////bg.myElementBufferData.myTextureRect = { 0,0,1,1 };
	////bg.myElementBufferData.myPivot = myPivot;
	////bg.myElementBufferData.myPosition = myScreenSpacePosition;
	////bg.myElementBufferData.myPosition.x -= myFontOffset.x;
	////bg.myElementBufferData.mySize = { myWidth,myHeight };

	//DXMRenderer::AddDrawSurface(bg);
	
}

void DXMUI::TextElement::SetPosition(const float aX, const float aY)
{
	auto clientRect = RECT();
	GetClientRect(DXM_D3D11_Interface::GetHWND(), &clientRect);
	auto windowWidth  =  static_cast<float>(clientRect.right - clientRect.left);
	auto windowHeight =  static_cast<float>(clientRect.bottom - clientRect.top);

	auto adjustedPosition = AdjustByAlignmentAndPivot({ aX, aY }, myAlignment, {0,0}, { myWidth, myHeight });

	myRenderText.myOrigin.x = windowWidth * myWidth * myPivot.x;
	myRenderText.myPosition = Vector2{ adjustedPosition.x * windowWidth, adjustedPosition.y * windowHeight };
	myScreenSpacePosition	= adjustedPosition;
}

DXMUI::Vector2 DXMUI::TextElement::GetPosition()
{
	return myScreenSpacePosition;
}

void DXMUI::TextElement::SetStyle(const DXUIStyle& aStyle)
{
	myRenderText.myColor = aStyle.myColor;
	myWidth *= aStyle.mySize.x;
	myHeight *= aStyle.mySize.y;
	myRenderText.myScale = aStyle.mySize;
	myRenderText.myFont = aStyle.myFont;
	myAlignment = aStyle.myAlignment;
	myPivot = aStyle.myPivot;
}
