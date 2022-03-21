#pragma once
#include "Utility\DXMUI_Util.h"
#include <string>

namespace DXMUI
{
	struct DXMRenderText
	{
		Color myColor = {0.f,0.f,0.f,1.f};
		Vector2 myPosition;
		Vector2 myScale;
		Vector2 myOrigin;
		float myRotation;
		std::wstring myText;
	};
}

