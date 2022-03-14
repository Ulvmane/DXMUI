#include "Canvas.h"
#include "Elements\DivElement.h"
void DXMUI::Canvas::Render()
{
	for (ElementContainer& container : myContainers)
	{
		for (auto& element : container.myElements)
		{
			element->Render();
		}
		printf("\n");
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
			containerHeight = std::max(containerHeight, element->GetHeight());
		}

		for (auto divPtr : divs)
		{
			divPtr->SetHeight(containerHeight);
		}

		y += containerHeight;
	}
}
