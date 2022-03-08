#pragma once
#include "Canvas\ICanvasElement.h"

namespace DXMUI
{
	class DivElement : public ICanvasElement
	{
		virtual void Render() override;
	};
}

