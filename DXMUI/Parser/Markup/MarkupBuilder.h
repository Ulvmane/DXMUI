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
		void   DivAppend(const int aDepth, std::string& aID, ICanvasElement* aElementToAppend);

		void   AddNode();
		void   Clear();
	private:
		struct NodeContent
		{
			std::string myID;
			ICanvasElement* myElement;
			std::vector<NodeContent> myChildren;
		};

		struct DXMBuildNode
		{
			DXMBuildNode* myChild = nullptr;
			NodeContent myContent;
		} myRoot;

	private:
		void GenerateContent(NodeContent* aContent, std::vector<DXMUI::ICanvasElement*>& aElems, std::vector<std::string>& aIDs);
		void Clear(DXMBuildNode* toClear);
		DXMBuildNode* myTail;
	};
}

