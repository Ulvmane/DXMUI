#pragma once
#include <string>

struct ID3D11DeviceContext;
struct ID3D11ShaderResourceView;

namespace DXMUI
{
	struct Color
	{
		float r = 0, g = 0, b = 0, a = 0;
	};

	struct Vector2
	{
		float x = 0, y = 0;
	};

	struct TextureRect
	{
		float startX = 0, startY = 0;
		float endX = 0, endY = 0;
	};

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
			float myPadding;
		} myElementBufferData;
		Texture myTexture;

	private:
	};
}
