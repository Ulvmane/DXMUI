#pragma once
#include <string>
#include "Utility\DXMUI_Util.h"
struct ID3D11DeviceContext;
struct ID3D11ShaderResourceView;

namespace DXMUI
{
	struct Texture
	{
		bool myWriteToGPU = false;
		ID3D11ShaderResourceView* myTexture = nullptr;
	};

	class DXMDrawSurface
	{
	public:
		DXMDrawSurface();
	
		~DXMDrawSurface()
		{
			myElementBufferData = ElementBufferData();
		}
	
		void Render(ID3D11DeviceContext* aContext);
		void SetTexture(std::wstring& aTexturePath);

		struct ElementBufferData
		{
			TextureRect myTextureRect = { 0,0,1,1 };
			Color myColor = { 1,1,1,1 };
			Vector2 myPosition = {0,0};
			Vector2 mySize = {0,0};
			Vector2 myPivot = {0,0};
			bool myHasTexture = false;
			bool padding1 = 0;
			bool padding2 = 0;
			bool padding3 = 0;
			bool padding4 = 0;
		} myElementBufferData;
		Texture myTexture;

	private:
	};
}
