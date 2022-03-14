#pragma once
#include "Canvas\ICanvasElement.h"
#include "D3D11_Interface\DXMDrawSurface.h"

#include <string>
#include <d3d11.h>
#include <memory>

namespace DXMUI
{
	class ImageElement : public ICanvasElement
	{
	public:
		ImageElement(const char* aPath);
		~ImageElement();
		virtual void Render() override; 
		virtual void SetPosition(const float aX, const float aY) override;

	private:
		std::string myPath;
		ID3D11ShaderResourceView* myTexture;

		DXMDrawSurface mySurface;
	};
}

