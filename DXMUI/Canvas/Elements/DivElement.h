#pragma once
#include "Canvas\ICanvasElement.h"
#include "D3D11_Interface\DXMDrawSurface.h"
namespace DXMUI
{
	class DivElement : public ICanvasElement
	{
	public:
		~DivElement() = default;
		DivElement();
		virtual void Render() override;
		virtual void SetPosition(const float aX, const float aY) override;
		virtual Vector2 GetPosition() override;
		void SetHeight(const float aHeight);
		void SetStyle(const struct DXUIStyle& aStyle) override;
	private:
		DXMDrawSurface mySurface;
	};
}

