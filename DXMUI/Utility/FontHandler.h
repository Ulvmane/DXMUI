#pragma once
#include <vector>
#include <string>
#include <memory>

namespace DirectX
{
	class SpriteFont;
}

namespace DXMUI
{
	using FontMapping = std::pair<std::string, std::unique_ptr<DirectX::SpriteFont>>;
	class FontHandler
	{
	public:
		static DirectX::SpriteFont* GetSpriteFont(const std::string& aFontPath);
	private:
		static DirectX::SpriteFont* LoadSpriteFont(const std::string& aFontPath);
		static std::vector<FontMapping> myFontMap;
	};
}

