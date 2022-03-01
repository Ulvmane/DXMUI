#pragma once
#include "ICanvasElement.h"
namespace DXMUI
{
	class IInteractableElement : public ICanvasElement
	{
	public:
		virtual void Interact() = 0;
	};
}