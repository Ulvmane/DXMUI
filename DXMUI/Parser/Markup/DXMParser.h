#pragma once
#include <string>
#include "MarkupBuilder.h"
#include "Canvas\Canvas.h"

namespace DXMUI
{
	class DXMParser
	{
	public:
		DXMBuilder Parse(const std::wstring& aPath);
		void	   Unparse(const std::wstring& aPath, const Canvas* aCanvas);
	};
}

