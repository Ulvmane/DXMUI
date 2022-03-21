#pragma once
#include "ICanvasElement.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "Parser\Styles\DXStyleSheet.h"

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
		void ApplyStyle(const DXStyleSheet& aStyleSheet);
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

