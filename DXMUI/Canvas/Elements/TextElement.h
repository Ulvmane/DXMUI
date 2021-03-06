#pragma once
#include "D3D11_Interface\DXMRenderText.h"
#include "Canvas\ICanvasElement.h"

namespace DXMUI
{
	class TextElement : public ICanvasElement
	{
	public:
		~TextElement() = default;
		TextElement(const char* aInData);
		virtual void Render() override;
		virtual void SetPosition(const float aX, const float aY) override;
		virtual Vector2 GetPosition() override;
	private:
		DXMRenderText myRenderText;
		Vector2 myScreenSpacePosition;
		Vector2 myFontOffset;
		Vector2 myScale = {1.f,1.f};
		virtual void SetStyle(const DXUIStyle& aStyle) override;
	};
}

