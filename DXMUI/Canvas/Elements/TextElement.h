#pragma once
#include <string>
#include "Canvas\ICanvasElement.h"
namespace DXMUI
{
	class TextElement : public ICanvasElement
	{
	public:
		TextElement(const char* aInData);
		virtual void Render() override;
	private:
		std::string myData;
	};
}

