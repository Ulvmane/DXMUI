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

		struct ElementContainer
		{
			std::vector <std::string> myIdentifier;
			std::vector<ICanvasElement*> myElements;
		};
		std::vector<ElementContainer> myContainers;

	};
}

