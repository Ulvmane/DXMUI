#include "DXSParser.h"
#include "Canvas\Elements\TextElement.h"
#include "Canvas\Elements\ImageElement.h"
#include "Canvas\Elements\ButtonElement.h"
#include "Canvas\Elements\DivElement.h"
#include <assert.h>
#include <filesystem>
#include <fstream>
#include <sstream>

DXMUI::DXSParser::DXSParser()
{
	myStyleTypeMap["Color"] = eStyleType::Color;
	myStyleTypeMap["color"] = eStyleType::Color;
	myStyleTypeMap["scaleX"] = eStyleType::SizeX;
	myStyleTypeMap["scaleY"] = eStyleType::SizeY;
	myStyleTypeMap["AlignX"] = eStyleType::AlignmentX;
	myStyleTypeMap["AlignY"] = eStyleType::AlignmentY;
	myStyleTypeMap["alignX"] = eStyleType::AlignmentX;
	myStyleTypeMap["alignY"] = eStyleType::AlignmentY;
	myStyleTypeMap["font"] = eStyleType::Font;
	myStyleTypeMap["Font"] = eStyleType::Font;
	myStyleTypeMap["pivotX"] = eStyleType::PivotX;
	myStyleTypeMap["pivotY"] = eStyleType::PivotY;
	myStyleTypeMap["margin"] = eStyleType::Margin;
	myStyleTypeMap["padding"] = eStyleType::Padding;
	myStyleTypeMap["border"] = eStyleType::Border;
}

DXMUI::DXStyleSheet DXMUI::DXSParser::Parse(const std::wstring& aPath)
{
	DXStyleSheet result;
	assert(std::filesystem::exists(aPath) && "Specified path does not exist");

	std::string buffer;
	std::ifstream file(aPath);
	file.seekg(0, std::ios::end);
	buffer.resize(file.tellg());
	file.seekg(0);
	file.read(buffer.data(), buffer.size());

	for (auto& c : buffer)
	{
		switch (c)
		{
			case '.':
				if (myBuffer == eCurrentBuffer::Value)
				{
					myBuffers[static_cast<unsigned int>(myBuffer)] += c;
					break;
				}
				myIdentifierBuffer = std::string();
				myBuffers[static_cast<unsigned int>(eCurrentBuffer::Identifier)] = std::string();
				myBuffer = eCurrentBuffer::Identifier;
				break;
			case ',':
			case ':':
				ParseLine(result);
				break;
			case '\n':
			case '\t':
			case '\0':
			case '#':
			case ' ':
				break;
			default:
				myBuffers[static_cast<unsigned int>(myBuffer)] += c;
				break;
		}
	}
	return result;
}

void DXMUI::DXSParser::Unparse(const std::wstring& aPath, const Canvas* aCanvas)
{
	//@TODO Read canvas and write to file.
}

void DXMUI::DXSParser::ParseLine(DXStyleSheet& aBuilder)
{
	switch (myBuffer)
	{
		case eCurrentBuffer::Identifier:
			myBuffer = eCurrentBuffer::Style;
			break;
		case eCurrentBuffer::Style:
			myBuffer = eCurrentBuffer::Value;
			break;
		case eCurrentBuffer::Value:
			ParseData(aBuilder);
			break;
		default:
			break;
	}
}

void DXMUI::DXSParser::ParseData(DXStyleSheet& aBuilder)
{
	auto& IDBuffer = myBuffers[static_cast<unsigned int>(eCurrentBuffer::Identifier)];
	auto& valueBuffer = myBuffers[static_cast<unsigned int>(eCurrentBuffer::Value)];
	auto& styleBuffer = myBuffers[static_cast<unsigned int>(eCurrentBuffer::Style)];
	auto type = myStyleTypeMap.find(styleBuffer);
	if (type == myStyleTypeMap.end())
		assert(false && "Syntax Error, incorrect style tag");

	aBuilder.SetIdentifier(IDBuffer);
	switch (type->second)
	{
		case eStyleType::SizeX:
			aBuilder.SetSizeX(IDBuffer, BufferToFloat(valueBuffer));
			break;
		case eStyleType::SizeY:
			aBuilder.SetSizeY(IDBuffer, BufferToFloat(valueBuffer));
			break;
		case eStyleType::Color:
			aBuilder.SetColor(IDBuffer, BufferToColor(valueBuffer));
			break;
		case eStyleType::Font:
			aBuilder.SetFont(IDBuffer, valueBuffer);
			break;
		case eStyleType::AlignmentX:
			aBuilder.SetAlignX(IDBuffer, BufferToFloat(valueBuffer));
			break;
		case eStyleType::AlignmentY:
			aBuilder.SetAlignY(IDBuffer, BufferToFloat(valueBuffer));
			break;
		case eStyleType::PivotX:
			aBuilder.SetPivotX(IDBuffer, BufferToFloat(valueBuffer));
			break;
		case eStyleType::PivotY:
			aBuilder.SetPivotY(IDBuffer, BufferToFloat(valueBuffer));
			break;
		case eStyleType::Padding:
		{
			auto size = BufferToFloat(valueBuffer);
			aBuilder.SetPadding(IDBuffer, {size,size,size,size});
		}
			break;
		case eStyleType::Margin:
		{
			auto size = BufferToFloat(valueBuffer);
			aBuilder.SetMargin(IDBuffer, { size,size,size,size });
		}
			break;
		case eStyleType::Border:
		{
			auto size = BufferToFloat(valueBuffer);
			aBuilder.SetBorder(IDBuffer, { size,size,size,size });
		}
			break;
		default:
			break;
	}

	valueBuffer = std::string();
	styleBuffer = std::string();
	myBuffer = eCurrentBuffer::Style;
}


void DXMUI::DXSParser::AttachDataToBuilder(DXStyleSheet& aBuilder)
{

}

void DXMUI::DXSParser::AppendData(DXStyleSheet& aBuilder, ICanvasElement* aElement)
{

}

float DXMUI::DXSParser::BufferToFloat(std::string& aBuffer)
{
	//TODO Alternative returns based on input suffix
	auto stringToFloat = std::stof(aBuffer);

	return stringToFloat;
}

DXMUI::Color DXMUI::DXSParser::BufferToColor(std::string& aBuffer)
{
	if (aBuffer.length() < 8)
	{
		assert(false && "Invalid Color");
		return Color{ 0, 0, 0, 0 };
	}
	UINT16 r, g, b, a;
	auto result = sscanf_s(aBuffer.c_str(), "%2hx%2hx%2hx%2hx", &r, &g, &b, &a);
	if (result < 4)
	{
		assert(false && "Invalid Color");
		return Color{ 0, 0, 0, 0 };
	}

	auto fR = static_cast<float>(r) / 255.f;
	auto fG = static_cast<float>(g) / 255.f;
	auto fB = static_cast<float>(b) / 255.f;
	auto fA = static_cast<float>(a) / 255.f;

	return Color{fR, fG, fB, fA};
}
