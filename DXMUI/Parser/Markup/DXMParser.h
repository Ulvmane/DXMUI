#pragma once
#include <string>
#include "MarkupBuilder.h"
#include "Canvas\Canvas.h"
#include <map>
#include <functional>
#include <stack>

namespace DXMUI
{
	class DXMParser
	{
	public:
		DXMParser();
		DXMBuilder Parse(const std::wstring& aPath);
		void	   Unparse(const std::wstring& aPath, const Canvas* aCanvas);
	
	private:
		void ParseTag(DXMBuilder& aBuilder);
		void AttachDataToBuilder(DXMBuilder& aBuilder);
		void AppendData(DXMBuilder& aBuilder, ICanvasElement* aElement);
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

