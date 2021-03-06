#include "DXMTextRenderer.h"
#include <d3d11.h>
#include "Utility\FontHandler.h"
std::unique_ptr<DirectX::SpriteFont> DXMUI::DXMTextRenderer::mySpriteFont;
std::vector<DXMUI::DXMRenderText> DXMUI::DXMTextRenderer::ourDrawTexts;

bool  DXMUI::DXMTextRenderer::Init(ID3D11DeviceContext* aContext, ID3D11Device* aDevice)
{	 
	mySpriteBatch = std::make_unique<DirectX::SpriteBatch>(aContext);
	mySpriteFont  = std::make_unique<DirectX::SpriteFont>(aDevice, L"Courier New.spritefont");
	return true;
}

void DXMUI::DXMTextRenderer::Render()
{
	mySpriteBatch->Begin(DirectX::SpriteSortMode::SpriteSortMode_Texture);
	for (auto& text : ourDrawTexts)
	{
		auto position = DirectX::XMFLOAT2(text.myPosition.x, text.myPosition.y);
		auto scale = DirectX::XMFLOAT2(text.myScale.x, text.myScale.y);
		auto origin = DirectX::XMFLOAT2(text.myOrigin.x, text.myOrigin.y);
		auto color = DirectX::XMVECTORF32{ text.myColor.r, text.myColor.g, text.myColor.b, text.myColor.a };
		auto font = text.myFont != "" ? text.myFont : std::string("Courier New.spritefont");
		FontHandler::GetSpriteFont(font)->DrawString
		(
			mySpriteBatch.get(),
			text.myText.c_str(),
			position, 
			color,
			text.myRotation,
			origin,
			scale,
			DirectX::SpriteEffects::SpriteEffects_None
		);
	}
	mySpriteBatch->End();
	ourDrawTexts.clear();
}

void DXMUI::DXMTextRenderer::AddText(DXMRenderText& aText)
{
	ourDrawTexts.emplace_back(DXMRenderText(aText));
}
