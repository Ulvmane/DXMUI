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
		__forceinline virtual float GetHeight() {return myHeight;}
		__forceinline virtual float GetWidth()  {return myWidth ;}
		virtual void SetStyle(const class DXUIStyle& aStyle) = 0;
	protected:
		float myHeight = 0;
		float myWidth  = 0;
		Vector2 myAlignment;
		Vector2 myPivot;
	};
}

