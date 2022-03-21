#include "DXStyleSheet.h"

bool DXMUI::DXStyleSheet::SetSizeX(const std::string& aID, float aX)
{
	auto style = myStyleMap.find(aID);
	if (style == myStyleMap.end())
		return false;
	style->second.mySize.x = aX;
	return true;
}

bool DXMUI::DXStyleSheet::SetSizeY(const std::string& aID, float aY)
{
	auto style = myStyleMap.find(aID);
	if (style == myStyleMap.end())
		return false;
	style->second.mySize.y = aY;
	return true;
}

bool DXMUI::DXStyleSheet::SetColor(const std::string& aID, const Color& aColor)
{
	auto style = myStyleMap.find(aID);
	if (style == myStyleMap.end())
		return false;
	style->second.myColor = aColor;
	return true;
}

bool DXMUI::DXStyleSheet::SetAlignX(const std::string& aID, float aX)
{
	//auto style = myStyleMap.find(aID);
	//if (style == myStyleMap.end())
	//	return false;
	//style->second.myColor = aColor;
	return true;
}

bool DXMUI::DXStyleSheet::SetAlignY(const std::string& aID, float aY)
{
	//auto style = myStyleMap.find(aID);
	//if (style == myStyleMap.end())
	//	return false;
	//style->second.myColor = aColor;
	return true;
}

bool DXMUI::DXStyleSheet::SetFont(const std::string& aID, const std::string& aPath)
{
	auto style = myStyleMap.find(aID);
	if (style == myStyleMap.end())
		return false;
	style->second.myFont = aPath;
	return true;
}

void DXMUI::DXStyleSheet::SetIdentifier(const std::string& aID)
{
	if (myStyleMap.find(aID) != myStyleMap.end())
		return;
	myStyleMap[aID] = DXUIStyle();
}
