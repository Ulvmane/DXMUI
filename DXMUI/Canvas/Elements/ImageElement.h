#pragma once
#include "Canvas\ICanvasElement.h"
#include <string>
namespace DXMUI
{
	class ImageElement : public ICanvasElement
	{
	public:
		ImageElement(const char* aPath);
		virtual void Render() override; 
	private:
		std::string myPath; // @TODO this should be a DX11 SRV.
	};
}

