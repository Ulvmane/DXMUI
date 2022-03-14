#pragma once
#include "ICanvasElement.h"
#include <string>
#include <vector>
#include <memory>

namespace DXMUI
{
	class Canvas
	{
	public:
		~Canvas() = default;
		void Render();
		void Init();
	private:
		friend class DXMBuilder;

		struct ElementContainer
		{
			std::vector <std::string> myIdentifier;
			std::vector<std::shared_ptr<ICanvasElement>> myElements;
		};
		std::vector<ElementContainer> myContainers;

	};
}

