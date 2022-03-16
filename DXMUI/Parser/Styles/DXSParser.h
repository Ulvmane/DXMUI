#pragma once
#include <string>
#include "DXUIStyle.h"
#include "Canvas\Canvas.h"
#include <map>
#include <functional>
#include <stack>

namespace DXMUI
{
	class DXSParser
	{
	public:
		DXSParser();
		DXUIStyle Parse(const std::wstring& aPath);
		void	   Unparse(const std::wstring& aPath, const Canvas* aCanvas);
	
	private:
		void ParseTag(DXUIStyle& aBuilder);
		void AttachDataToBuilder(DXUIStyle& aBuilder);
		void AppendData(DXUIStyle& aBuilder, ICanvasElement* aElement);
	private:
		enum class eTagType
		{
			Text,
			Div,
			Image,
			Button
		};

		enum class eCurrentBuffer
		{
			InputField,
			Element,
			Tag
		} myBuffer = eCurrentBuffer::InputField;

	private:
		std::string myTagBuffer;
		std::stack<std::string> myContentStack;
		std::stack<std::string> myIDStack;
		std::stack<eTagType> myTypeStack;
		unsigned int myDepth;
	};
}

