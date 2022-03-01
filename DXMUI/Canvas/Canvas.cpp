#include "Canvas.h"
void DXMUI::Canvas::Render()
{
	for (CanvasDweller& dweller : myDwellers)
	{
		printf("ID: ");
		printf(dweller.myIdentifier.c_str()); 
		printf("\n");
		dweller.myElement->Render();
	}
}