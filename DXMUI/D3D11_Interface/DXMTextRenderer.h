#pragma once
#include <vector>
#include <memory>

#include <SpriteBatch.h>
#include <SpriteFont.h>
#include "DXMRenderText.h"

struct ID3D11DeviceContext;
struct  ID3D11Device;
namespace DXMUI
{
	class DXMTextRenderer
	{
	public:
		bool Init(struct ID3D11DeviceContext* aContext, ID3D11Device* aDevice);
		void Render();
		static void AddText(struct DXMRenderText& aText);
		static __forceinline DirectX::SpriteFont* GetDefaultSpriteFont() { return mySpriteFont.get(); }
	private:
		static std::vector<DXMRenderText> ourDrawTexts;
		std::unique_ptr<DirectX::SpriteBatch> mySpriteBatch;
		static std::unique_ptr<DirectX::SpriteFont> mySpriteFont;
	};
}

