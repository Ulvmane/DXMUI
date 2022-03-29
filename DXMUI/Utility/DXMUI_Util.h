#pragma once
#include <memory>
#include "FontHandler.h"
#include <string>

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
	static unsigned int ourReferenceWidth = 1280;
	static unsigned int ourReferenceHeight = 720;

	struct Color
	{
		float r = 0, g = 0, b = 0, a = 0;
	};

	struct Vector2
	{
		float x = 0, y = 0;
	};

	struct Box
	{
		float left	 { 0.f};
		float right	 { 0.f };
		float top	 { 0.f };
		float bottom { 0.f };
	};

	struct TextureRect
	{
		float startX = 0, startY = 0;
		float endX = 0, endY = 0;
	};

	Vector2 AdjustByAlignmentAndPivot(const Vector2& aPosition, const Vector2& aAlignment, const Vector2& aPivot, const Vector2& aElementBounds);

	Vector2 GetFontOffset(DirectX::SpriteFont* aFont, const std::wstring& aText );
}