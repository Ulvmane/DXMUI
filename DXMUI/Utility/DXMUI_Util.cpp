#include "DXMUI_Util.h"
#include <SpriteFont.h>


DXMUI::Vector2 DXMUI::AdjustByAlignmentAndPivot(const DXMUI::Vector2& aPosition,
												const DXMUI::Vector2& aAlignment,
												const DXMUI::Vector2& aPivot,
												const Vector2& aElementBounds)
{
	auto remaingX = (1 - aPosition.x);
	auto remaingY = (1 - aPosition.y);

	auto alignAdjustedX = aPosition.x + aAlignment.x * remaingX;
	auto alignAdjustedY = aPosition.y + aAlignment.y * remaingY;

	auto pivotAlignAdjustedX = alignAdjustedX; //- aPivot.x * aElementBounds.x;
	auto pivotAlignAdjustedY = alignAdjustedY; //- aPivot.y * aElementBounds.y;

	return { pivotAlignAdjustedX, pivotAlignAdjustedY };
}

DXMUI::Vector2 DXMUI::GetFontOffset(DirectX::SpriteFont* aFont, const std::wstring& aText)
{
	auto drawRect = aFont->MeasureDrawBounds(aText.c_str(), DirectX::XMFLOAT2(0.f, 0.f), true);
	auto offsetX = static_cast<float>(drawRect.left) / ourReferenceWidth;
	auto offsetY = static_cast<float>(drawRect.top) / ourReferenceHeight;
	return { offsetX, offsetY };
}
