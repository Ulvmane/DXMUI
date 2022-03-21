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
	auto dimension = spriteFont->MeasureDrawBounds(myRenderText.myText.c_str(), DirectX::XMFLOAT2(0.f, 0.f));

	auto clientRect = RECT();
	GetClientRect(DXM_D3D11_Interface::GetHWND(), &clientRect);

	myWidth  = (dimension.right - dimension.left) / static_cast<float>(clientRect.right - clientRect.left);
	myHeight = (dimension.bottom - dimension.top) / static_cast<float>(clientRect.bottom - clientRect.top);
}

void DXMUI::TextElement::Render()
{
	DXMTextRenderer::AddText(myRenderText);
}

void DXMUI::TextElement::SetPosition(const float aX, const float aY)
{
	auto clientRect = RECT();
	GetClientRect(DXM_D3D11_Interface::GetHWND(), &clientRect);
	auto windowWidth  =  static_cast<float>(clientRect.right - clientRect.left);
	auto windowHeight =  static_cast<float>(clientRect.bottom - clientRect.top);
	myRenderText.myPosition = Vector2{ aX * windowWidth, aY * windowHeight };
	myScreenSpacePosition = Vector2{ aX, aY };
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
}
