#pragma once
#include "ICanvasElement.h"
#include <string>
#include <vector>

namespace DXMUI
{
	class Canvas
	{
	public:
		void Render();
	private:
		friend class DXMBuilder;

		struct CanvasDweller
		{
			std::string myIdentifier;
			ICanvasElement* myElement;
		};
		std::vector<CanvasDweller> myDwellers;

	};
}

