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
	Color,
	Font,
	Count,
};

namespace DXMUI
{
	struct DXUIStyle
	{
		std::string myFont;
		Color myColor;
		Vector2 mySize;
		Vector2 alignment;
	};
}

