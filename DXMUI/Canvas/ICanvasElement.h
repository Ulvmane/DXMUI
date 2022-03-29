#pragma once
#include "Utility\DXMUI_Util.h"
namespace DXMUI
{
	class ICanvasElement
	{
	public: 
		virtual ~ICanvasElement() = default;
		virtual void Render() = 0;
		virtual void SetPosition(const float aX, const float aY) = 0;
		virtual Vector2 GetPosition() = 0;
		__forceinline virtual float GetHeight() 
		{
			return myHeight + myPadding.bottom + myPadding.top + myBorder.bottom + myBorder.top + myMargin.top + myMargin.bottom;
		}
		__forceinline virtual float GetWidth() 
		{
			return myWidth + myPadding.left + myPadding.right + myBorder.left + myBorder.right + myMargin.left + myMargin.right ;
		}
		virtual void SetStyle(const struct DXUIStyle& aStyle) = 0;
	protected:
		float myHeight = 0;
		float myWidth  = 0;

		Box myPadding;
		Box myBorder;
		Box myMargin;

		Vector2 myAlignment;
		Vector2 myPivot;
	};
}

