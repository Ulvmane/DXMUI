#include "ImageElement.h"

DXMUI::ImageElement::ImageElement(const char* aPath)
{
	myPath = aPath; //@TODO load srv.
}

#include <iostream> // temp
void DXMUI::ImageElement::Render()
{
	std::cout << "I am the image -> " << myPath;
}
