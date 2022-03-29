#pragma once
#include <array>
#include <string>
#include "Utility\DXMUI_Util.h"
enum class eStyleType : unsigned char
{
	None,
	SizeX,
	SizeY,
	AlignmentX,
	AlignmentY,
	PivotX,
	PivotY,
	Color,
	Font,
	Count,
	Margin,
	Padding,
	Border
};

namespace DXMUI
{
	struct DXUIStyle
	{
		std::string myFont{""};
		Color myColor{0.f,0.f,0.f,1.f};
		Vector2 mySize{1.f, 1.f};
		Vector2 myAlignment{0.f, 0.f};
		Vector2 myPivot{0.f, 0.f};
		Box myMargin;
		Box myPadding;
		Box myBorder;
	};
}

