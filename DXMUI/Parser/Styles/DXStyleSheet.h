#pragma once
#include "DXUIStyle.h"
#include <unordered_map>

namespace DXMUI
{
	class DXStyleSheet
	{
	public:
		bool SetSizeX(const std::string& aID, float aX);
		bool SetSizeY(const std::string& aID, float aY);
		bool SetColor(const std::string& aID, const Color& aColor);
		bool SetAlignX(const std::string& aID, float aX);
		bool SetAlignY(const std::string& aID, float aY);
		bool SetPivotX(const std::string& aID, float aX);
		bool SetPivotY(const std::string& aID, float aY);
		bool SetFont(const std::string& aID, const std::string& aPath);

		__inline DXUIStyle& GetStyle(const std::string& aID) { return myStyleMap[aID]; }
		void SetIdentifier(const std::string& aID);
	private:
		friend class Canvas;
		std::unordered_map<std::string, DXUIStyle> myStyleMap;
	};
}

