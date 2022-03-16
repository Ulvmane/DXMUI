#include "TextElement.h"
#include "D3D11_Interface\DXMTextRenderer.h"
#include "D3D11_Interface\DXM_D3D11_Interface.h"

DXMUI::TextElement::TextElement(const char* aInData)
{
	auto data = std::string(aInData);
	myRenderText.myPosition = Vector2{ 0,0 };
	myRenderText.myRotation = 0;
	myRenderText.myScale = Vector2{ 1,1 };
	myRenderText.myText = std::wstring(data.begin(), data.end());

	auto spriteFont = DXMTextRenderer::GetDefaultSpriteFont();
	auto dimension = spriteFont->MeasureString(myRenderText.myText.c_str(), false) ;

	auto clientRect = RECT();
	GetClientRect(DXM_D3D11_Interface::GetHWND(), &clientRect);
	
	myWidth  = DirectX::XMVectorGetX(dimension) / static_cast<float>(clientRect.right - clientRect.left);
	myHeight = DirectX::XMVectorGetY(dimension) / static_cast<float>(clientRect.bottom - clientRect.top);
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
