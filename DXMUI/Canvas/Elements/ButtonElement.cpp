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

	auto clientRect = RECT();
	GetClientRect(DXM_D3D11_Interface::GetHWND(), &clientRect);
	auto clientWidth  = static_cast<float>(clientRect.right - clientRect.left);
	auto clientHeight = static_cast<float>(clientRect.bottom - clientRect.top);

	auto dimension = spriteFont->MeasureDrawBounds(myRenderText.myText.c_str(), DirectX::XMFLOAT2(0.f, 0.f));
	myWidth = (dimension.right - dimension.left) / static_cast<float>(clientRect.right - clientRect.left);
	myHeight = (dimension.bottom - dimension.top) / static_cast<float>(clientRect.bottom - clientRect.top);
	myRenderText.myOrigin = { 0.f, 0.f};

	mySurface.myElementBufferData.myHasTexture = false;
	mySurface.myElementBufferData.myColor = Color{ 0,0,0,0.5f };
	mySurface.myElementBufferData.myPivot = Vector2{ 0,0 };
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
	mySurface.myElementBufferData.myPosition = Vector2{aX, aY};

	auto clientRect = RECT();
	GetClientRect(DXM_D3D11_Interface::GetHWND(), &clientRect);
	auto windowWidth = static_cast<float>(clientRect.right - clientRect.left);
	auto windowHeight = static_cast<float>(clientRect.bottom - clientRect.top);
	myRenderText.myPosition = Vector2{ aX * windowWidth, aY * windowHeight };
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
}
