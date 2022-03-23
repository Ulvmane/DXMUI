#pragma once
#include "Utility\DXMUI_Util.h"
#include <string>

namespace DXMUI
{
	struct DXMRenderText
	{
		Color myColor		{ 0.f, 0.f, 0.f, 1.f};
		Vector2 myPosition  { 0.f, 0.f};
		Vector2 myScale		{ 1.f, 1.f };
		Vector2 myOrigin	{ 0.f, 0.f};
		float myRotation	{ 0.f };
		std::wstring myText { L"" };
		std::string myFont  { "" };
	};
}

