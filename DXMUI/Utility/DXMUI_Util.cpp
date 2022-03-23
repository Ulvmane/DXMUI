#include "DXMUI_Util.h"

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
};