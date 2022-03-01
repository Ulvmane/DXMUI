#include "MarkupBuilder.h"

DXMUI::DXMBuilder::DXMBuilder()
{
	myLeaf = &myRoot;
}

DXMUI::Canvas DXMUI::DXMBuilder::Build()
{
	Canvas canvas;

	DXMBuildNode* inspectingNode = myRoot.myChild;

	while (inspectingNode != nullptr)
	{
		canvas.myDwellers.push_back({ inspectingNode->myID, inspectingNode->myElements[0] });
		
		inspectingNode = inspectingNode->myChild;
	}
	return canvas; 
}

void DXMUI::DXMBuilder::DivAppend(ICanvasElement* aElementToAppend)
{
	DXMBuildNode* leaf = myLeaf;
	leaf->myElements.emplace_back(aElementToAppend);
}

void DXMUI::DXMBuilder::Append(const std::string& aID, ICanvasElement* aElementToAppend)
{
	DXMBuildNode* leaf = myLeaf;
	leaf->myChild = new DXMBuildNode();
	leaf->myChild->myID = aID;
	leaf->myChild->myElements.emplace_back(aElementToAppend);
	myLeaf = leaf->myChild;
}

void DXMUI::DXMBuilder::Clear()
{
	Clear(&myRoot);
}

void DXMUI::DXMBuilder::Clear(DXMBuildNode* toClear)
{
	if (toClear->myChild != nullptr)
	{
		Clear(toClear->myChild);
		delete toClear->myChild;
		toClear->myChild = nullptr;
	}
	for (auto& it : toClear->myElements)
	{
		delete it;
		it = nullptr;
	}
	toClear->myElements.shrink_to_fit();
}
