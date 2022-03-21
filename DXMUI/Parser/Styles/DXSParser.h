#pragma once
#include <string>
#include "DXStyleSheet.h"
#include "Canvas\Canvas.h"
#include <array>
namespace DXMUI
{
	class DXSParser
	{
	public:
		DXSParser();
		DXStyleSheet Parse(const std::wstring& aPath);
		void	     Unparse(const std::wstring& aPath, const Canvas* aCanvas);
	
	private:
		void ParseLine(DXStyleSheet& aBuilder);
		void ParseData(DXStyleSheet& aBuilder);
		void AttachDataToBuilder(DXStyleSheet& aBuilder);
		void AppendData(DXStyleSheet& aBuilder, ICanvasElement* aElement);
	private:

		enum class eCurrentBuffer
		{
			Identifier,
			Style,
			Value
		} myBuffer = eCurrentBuffer::Identifier;

	private:
		float BufferToFloat(std::string& aBuffer);
		Color BufferToColor(std::string& aBuffer);

		std::string myIdentifierBuffer;
		std::string myStyleBuffer;
		std::string myValueBuffer;

		std::array<std::string, 3> myBuffers;
		std::unordered_map<std::string, eStyleType> myStyleTypeMap;
	};
}

