#pragma once
#include <string>
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
	private:
		std::string myData;
	};
}

