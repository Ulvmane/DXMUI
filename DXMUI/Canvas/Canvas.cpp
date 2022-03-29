#include "Canvas.h"
#include "Elements\DivElement.h"
#include "IInteractableElement.h"
#include <Windows.h>
#include "D3D11_Interface\DXM_D3D11_Interface.h"

void DXMUI::Canvas::Update()
{
	if ((GetKeyState(VK_LBUTTON) & 0x8000) == 0)
	{
		myLMBDown = false;
		return;
	}
	else if (myLMBDown)
	{
		return;
	}
	myLMBDown = true;

	POINT cursorPos;
	if (!GetCursorPos(&cursorPos))
		return;
	if (!ScreenToClient(DXM_D3D11_Interface::GetHWND(), &cursorPos))
		return;
	
	auto clientRect = RECT();
	GetClientRect(DXM_D3D11_Interface::GetHWND(), &clientRect);
	auto clientX = float{static_cast<float>(clientRect.right - clientRect.left) };
	auto clientY = float{static_cast<float>(clientRect.bottom - clientRect.top) };

	auto posX = static_cast<float>(cursorPos.x) / clientX;
	auto posY = static_cast<float>(cursorPos.y) / clientY;

	int i = 0;
	for (auto& container : myContainers)
	{
		for (auto& element : container.myElements)
		{
			auto ePosition = element->GetPosition();
			if (posX > ePosition.x && posX < ePosition.x + element->GetWidth() &&
				posY > ePosition.y && posY < ePosition.y + element->GetHeight())
			{
				auto interactable = dynamic_cast<IInteractableElement*>(element.get());
				if (interactable != nullptr)
				{
					interactable->Interact();
				}
			}
		}
	}
}

void DXMUI::Canvas::Render()
{
	for (ElementContainer& container : myContainers)
	{
		for (auto& element : container.myElements)
		{
			element->Render();
		}
	}
}

void DXMUI::Canvas::Init()
{
	auto x = float{ 0 };
	auto y = float{ 0 };

	for (ElementContainer& container : myContainers)
	{
		x = 0.f;
		auto containerHeight = float{0};

		std::vector<DivElement*> divs;
		for (auto& element : container.myElements)
		{
			auto div = dynamic_cast<DivElement*>(element.get());
			if ( div != nullptr)
			{
				divs.emplace_back(div);
			}
			element->SetPosition(x,y);
			x += element->GetWidth();
			containerHeight = max(containerHeight, element->GetHeight());
		}

		for (auto divPtr : divs)
		{
			divPtr->SetHeight(containerHeight);
		}

		y += containerHeight;
	}
}

void DXMUI::Canvas::SetCallback(const std::string& aID, std::function<void()> aFunction)
{
	for (auto& container : myContainers)
	{
		for (unsigned int i = 0; i < container.myElements.size(); i++)
		{
			if (container.myIdentifier[i] == aID)
			{
				auto interactable = dynamic_cast<IInteractableElement*>(container.myElements[i].get());
				if (interactable != nullptr)
				{
					interactable->myCallback = aFunction;
				}
			}
		}
	}
}

void DXMUI::Canvas::ApplyStyle(const DXStyleSheet& aStyleSheet)
{
	if(aStyleSheet.myStyleMap.find("img") != aStyleSheet.myStyleMap.end())
		ApplyStyleToElements("img", aStyleSheet.myStyleMap.at("img"));
	if(aStyleSheet.myStyleMap.find("t") != aStyleSheet.myStyleMap.end())
		ApplyStyleToElements("t", aStyleSheet.myStyleMap.at("t"));
	if(aStyleSheet.myStyleMap.find("button") != aStyleSheet.myStyleMap.end())
		ApplyStyleToElements("button", aStyleSheet.myStyleMap.at("button"));

	for (auto& idStylePair : aStyleSheet.myStyleMap)
	{
		ApplyStyleToContainers(idStylePair.first, idStylePair.second);
	}
	Init();
}

void DXMUI::Canvas::ApplyStyleToContainers(const std::string& aID, const DXUIStyle& aStyle)
{
	for (auto& container : myContainers)
	{
		for (unsigned int i = 0; i < container.myElements.size(); i++)
		{
			if (container.myIdentifier[i].compare(aID) == 0)
			{
				container.myElements[i]->SetStyle(aStyle);
			}
		}
	}
}


#include "Elements\ImageElement.h"
#include "Elements\TextElement.h" 
#include "Elements\ButtonElement.h"

void DXMUI::Canvas::ApplyStyleToElements(const std::string& aID, const DXUIStyle& aStyle)
{
	enum class elementType
	{
		Text, Button, Img
	} eType = elementType::Text;

	if (aID == "img")
		eType = elementType::Img;
	if (aID == "button")
		eType = elementType::Button;
	if (aID == "t")
		eType = elementType::Text;

	for (auto& container : myContainers)
	{
		if (container.myElements.size() < 1)
			continue;

		auto& e = container.myElements[0];
		switch (eType)
		{
			case elementType::Text:
				if (dynamic_cast<TextElement*>(e.get()) != nullptr)
					e->SetStyle(aStyle);
				break;
			case elementType::Button:
				if (dynamic_cast<ButtonElement*>(e.get()) != nullptr)
					e->SetStyle(aStyle);
				break;
			case elementType::Img:
				if (dynamic_cast<ImageElement*>(e.get()) != nullptr)
					e->SetStyle(aStyle);
				break;
			default:
				break;
		}
	}
}
