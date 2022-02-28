#pragma once
#include "Canvas\Canvas.h"
#include "Canvas\ICanvasElement.h"
#include <vector>

namespace DXMUI
{
	class DXMBuilder
	{
	public:
		Canvas Build();
		void   DivAppend(ICanvasElement* aElementToAppend);
		void   Append(ICanvasElement* aElementToAppend);
		void   Clear();

	private:
		struct DXMBuildNode
		{
			DXMBuildNode* myChild = nullptr;
			std::vector<ICanvasElement*> myElements;
		} myRoot;

	private:
		void Clear(DXMBuildNode* toClear);
		DXMBuildNode* FindLeaf();
	};
}

