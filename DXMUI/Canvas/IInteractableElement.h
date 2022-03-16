#pragma once
#include "ICanvasElement.h"
#include <functional>
namespace DXMUI
{
	class IInteractableElement : public ICanvasElement
	{
	public:
		virtual void Interact() { myCallback(); };
		std::function<void()> myCallback = [](){};
	};
}