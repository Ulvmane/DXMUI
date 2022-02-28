#pragma once
#include <string>
namespace DXMUI
{
	class IParsable;
	class IParser
	{
	public:
		virtual void Parse(std::string& aPath);
		virtual void Unparse(DXMUI::IParsable* aParsable, std::string& aPath);
	};
}

