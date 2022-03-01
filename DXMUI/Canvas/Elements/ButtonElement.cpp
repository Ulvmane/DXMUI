#include "ButtonElement.h"

DXMUI::ButtonElement::ButtonElement(const char* aText)
{
	myText = aText;
}

void DXMUI::ButtonElement::Interact()
{
	// @Todo cool callback magic
}
#include <iostream>
void DXMUI::ButtonElement::Render()
{
	std::cout << myText << std::endl;
}
