#include "TextElement.h"

DXMUI::TextElement::TextElement(const char* aInData)
{
	myData = std::string(aInData);
}

void DXMUI::TextElement::Render()
{
	printf(myData.c_str());
	// @Todo Send rendercommand to DX11Impl.
}
