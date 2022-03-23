#include "FontHandler.h"
#include <algorithm>
#include "D3D11_Interface\DXM_D3D11_Interface.h"
#include <SpriteFont.h>

std::vector<DXMUI::FontMapping> DXMUI::FontHandler::myFontMap;
DirectX::SpriteFont* DXMUI::FontHandler::GetSpriteFont(const std::string& aFontPath)
{
    auto isMapped = [aFontPath](const FontMapping& aLhs) { return aLhs.first == aFontPath; };
    auto mappedFont = std::find_if(std::begin(myFontMap), std::end(myFontMap), isMapped);
    if (mappedFont == std::end(myFontMap))
        return LoadSpriteFont(aFontPath);
    else
        return mappedFont->second.get();
}

DirectX::SpriteFont* DXMUI::FontHandler::LoadSpriteFont(const std::string& aFontPath)
{
    auto wStr = std::wstring(aFontPath.begin(), aFontPath.end());
    auto fontPtr = std::make_unique<DirectX::SpriteFont>(DXM_D3D11_Interface::GetDevice(), wStr.c_str());
    if (fontPtr)
    {
        myFontMap.emplace_back();
        myFontMap.back().first = aFontPath;
        myFontMap.back().second = std::move(fontPtr);
        return myFontMap.back().second.get();
    }
    else
    {
        return nullptr;
    }
}