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
	myStyleTypeMap["SizeX"] = eStyleType::SizeX;
	myStyleTypeMap["SizeY"] = eStyleType::SizeY;
	myStyleTypeMap["AlignmentX"] = eStyleType::AlignmentX;
	myStyleTypeMap["alignmentX"] = eStyleType::AlignmentX;
	myStyleTypeMap["alignmentY"] = eStyleType::AlignmentY;
	myStyleTypeMap["alignmentY"] = eStyleType::AlignmentY;
	myStyleTypeMap["font"] = eStyleType::Font;
	myStyleTypeMap["Font"] = eStyleType::Font;
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
	auto type = myStyleTypeMap.find(myStyleBuffer);
	if (type == myStyleTypeMap.end())
		assert(false && "Syntax Error, incorrect style tag");

	aBuilder.SetIdentifier(myIdentifierBuffer);
	switch (type->second)
	{
		case eStyleType::SizeX:
			aBuilder.SetSizeX(myIdentifierBuffer, BufferToFloat(myValueBuffer));
			break;								  
		case eStyleType::SizeY:					  
			aBuilder.SetSizeY(myIdentifierBuffer, BufferToFloat(myValueBuffer));
			break;								  
		case eStyleType::Color:					  
			aBuilder.SetColor(myIdentifierBuffer, BufferToColor(myValueBuffer));
			break;
		case eStyleType::Font:
			aBuilder.SetFont(myIdentifierBuffer, myValueBuffer);
			break;
		case eStyleType::AlignmentX:
			aBuilder.SetSizeX(myIdentifierBuffer, BufferToFloat(myValueBuffer));
			break;
		case eStyleType::AlignmentY:
			aBuilder.SetSizeX(myIdentifierBuffer, BufferToFloat(myValueBuffer));
			break;
		default:
			break;
	}

	myValueBuffer = std::string();
	myStyleBuffer = std::string();
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

	auto fR = static_cast<unsigned int>(r) / 255.f;
	auto fG = static_cast<unsigned int>(g) / 255.f;
	auto fB = static_cast<unsigned int>(b) / 255.f;
	auto fA = static_cast<unsigned int>(a) / 255.f;

	return Color{fR, fG, fB, fA};
}
