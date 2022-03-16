#pragma once
#include "ICanvasElement.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace DXMUI
{
	class Canvas
	{
	public:
		~Canvas() = default;
		void Update();
		void Render();
		void Init();
		void SetCallback(const std::string& aID, std::function<void()> aFunction);
	private:
		friend class DXMBuilder;

		struct ElementContainer
		{
			std::vector <std::string> myIdentifier;
			std::vector<std::shared_ptr<ICanvasElement>> myElements;
		};
		std::vector<ElementContainer> myContainers;
		bool myLMBDown;
	};
}

