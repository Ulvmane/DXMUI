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