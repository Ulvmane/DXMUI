#include "MarkupBuilder.h"

DXMUI::DXMBuilder::DXMBuilder()
{
	myTail = &myRoot;
}

DXMUI::Canvas DXMUI::DXMBuilder::Build()
{
	Canvas canvas;

	DXMBuildNode* inspectingNode = &myRoot;

	while (inspectingNode != nullptr)
	{
		std::vector<std::shared_ptr<ICanvasElement>> elems;
		std::vector<std::string> ids;

		if (inspectingNode->myContent.myElement != nullptr)
		{
			auto emptyPtr = std::shared_ptr<ICanvasElement>();
			emptyPtr.reset(inspectingNode->myContent.myElement);
			elems.emplace_back(emptyPtr);
			ids.emplace_back(inspectingNode->myContent.myID);
		}
		for (auto& content : inspectingNode->myContent.myChildren)
		{
			GenerateContent(&content, elems, ids);
		}

		canvas.myContainers.push_back({ ids, elems });
		inspectingNode = inspectingNode->myChild;
	}
	return canvas; 
}

void DXMUI::DXMBuilder::DivAppend(const int aDepth, std::string& aID, ICanvasElement* aElementToAppend)
{
	NodeContent* content = &myTail->myContent;
	for (int i = 1; i < aDepth; i++)
	{
		if (content->myChildren.size() < 1) { content->myChildren.emplace_back(); }
		content = &content->myChildren.back();
	}

	if (content->myElement != nullptr)
	{
		content->myChildren.emplace_back();
		content = &content->myChildren.back();
	}

	content->myID = aID;
	content->myElement = aElementToAppend;

}

void DXMUI::DXMBuilder::AddNode()
{
	DXMBuildNode* tail = myTail;
	tail->myChild = new DXMBuildNode();
	myTail = tail->myChild;
}

void DXMUI::DXMBuilder::Clear()
{
	Clear(&myRoot);
}

void DXMUI::DXMBuilder::GenerateContent(DXMUI::DXMBuilder::NodeContent* aContent, std::vector<std::shared_ptr<DXMUI::ICanvasElement>>& aElems, std::vector<std::string>& aIDs)
{
	aElems.emplace_back(aContent->myElement);
	aIDs.emplace_back(aContent->myID);
	for (auto& content : aContent->myChildren)
	{
		GenerateContent(&content, aElems, aIDs);
	}
}

void DXMUI::DXMBuilder::Clear(DXMBuildNode* toClear)
{
	if (toClear->myChild != nullptr)
	{
		Clear(toClear->myChild);
		delete toClear->myChild;
		toClear->myChild = nullptr;
	}
	//for (auto& content_list : toClear->myContent)
	//{
	//	for (auto& content : content_list)
	//	{
	//		delete content.myElement;
	//		content.myElement = nullptr;
	//	}
	//	
	//}
	//toClear->myContent.clear();
	//toClear->myContent.shrink_to_fit();
}
