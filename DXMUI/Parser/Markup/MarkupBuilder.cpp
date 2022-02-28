#include "MarkupBuilder.h"

DXMUI::Canvas DXMUI::DXMBuilder::Build()
{
	return Canvas(); // @TODO Generate Canvas from root
}

void DXMUI::DXMBuilder::DivAppend(ICanvasElement* aElementToAppend)
{
	DXMBuildNode* leaf = FindLeaf();
	leaf->myElements.emplace_back(aElementToAppend);
}

void DXMUI::DXMBuilder::Append(ICanvasElement* aElementToAppend)
{
	DXMBuildNode* leaf = FindLeaf();
	leaf->myChild = new DXMBuildNode();
	leaf->myChild->myElements.emplace_back(aElementToAppend);
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

DXMUI::DXMBuilder::DXMBuildNode* DXMUI::DXMBuilder::FindLeaf()
{
	DXMBuildNode* leaf = &myRoot;
	while (leaf->myChild != nullptr)
	{
		leaf = leaf->myChild;
	}
	return leaf;
}
