#include "ButtonElement.h"
#include "D3D11_Interface\DXMRenderer.h"

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

}

void DXMUI::ButtonElement::SetPosition(const float aX, const float aY)
{
}
