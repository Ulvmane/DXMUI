#include "Canvas.h"
void DXMUI::Canvas::Render()
{
	for (ElementContainer& container : myContainers)
	{
		for (ICanvasElement* element : container.myElements)
		{
			element->Render();
		}
		printf("\n");
	}
}