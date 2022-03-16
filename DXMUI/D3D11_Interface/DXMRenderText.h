#pragma once
#include "Utility\DXMUI_Util.h"
#include <string>

namespace DXMUI
{
	struct DXMRenderText
	{
		Vector2 myPosition;
		Vector2 myScale;
		float myRotation;
		std::wstring myText;
	};
}

