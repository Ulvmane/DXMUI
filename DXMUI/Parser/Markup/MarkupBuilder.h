#pragma once
#include "Canvas\Canvas.h"
#include "Canvas\ICanvasElement.h"
#include <vector>

namespace DXMUI
{
	class DXMBuilder
	{
	public:
		DXMBuilder();
		Canvas Build();
		void   DivAppend(ICanvasElement* aElementToAppend);
		void   Append(const std::string& aID, ICanvasElement* aElementToAppend);
		void   Clear();

	private:
		struct DXMBuildNode
		{
			std::string myID;
			DXMBuildNode* myChild = nullptr;
			std::vector<ICanvasElement*> myElements;
		} myRoot;

	private:
		void Clear(DXMBuildNode* toClear);
		DXMBuildNode* myLeaf;
	};
}

