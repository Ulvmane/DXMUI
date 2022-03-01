#pragma once
#include <string>
#include "MarkupBuilder.h"
#include "Canvas\Canvas.h"
#include <map>
#include <functional>

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
	private:
		enum class eTagType
		{
			Text,
			Div,
			Image,
			Button
		} myCurrentTag;

		enum class eCurrentBuffer
		{
			InputField,
			Tag
		} myBuffer = eCurrentBuffer::InputField;

	private:
		char myTagBuffer[64];
		char myInputFieldBuffer[256];
		unsigned short myTagCounter = 0;
		unsigned short myInputFieldCounter = 0;
		std::string myCurrentIdentifier = "";
	};
}

