#pragma once
#include <memory>
template <class T> void DXM_SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

namespace DXMUI
{
	struct Color
	{
		float r = 0, g = 0, b = 0, a = 0;
	};

	struct Vector2
	{
		float x = 0, y = 0;
	};

	struct TextureRect
	{
		float startX = 0, startY = 0;
		float endX = 0, endY = 0;
	};

}