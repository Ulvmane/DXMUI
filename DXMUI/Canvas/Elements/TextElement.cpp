#include "TextElement.h"

DXMUI::TextElement::TextElement(const char* aInData)
{
	myData = std::string(aInData);
}

void DXMUI::TextElement::Render()
{
	// @Todo Send rendercommand to DX11Impl.
}
