#include "DXMParser.h"
#include "Canvas\Elements\TextElement.h"
#include "Canvas\Elements\ImageElement.h"
#include "Canvas\Elements\ButtonElement.h"
#include <assert.h>
#include <filesystem>
#include <fstream>
#include <sstream>

DXMUI::DXMParser::DXMParser()
{
	memset(myTagBuffer, '\0', 64);
	memset(myInputFieldBuffer, '\0', 256);
}

DXMUI::DXMBuilder DXMUI::DXMParser::Parse(const std::wstring& aPath)
{
	DXMBuilder result;
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
			case '<':
				// Todo begin read tag.
				myBuffer = eCurrentBuffer::Tag;
				break;
			case '>':
				ParseTag(result);
				myBuffer = eCurrentBuffer::InputField;
				break;
			case '\n':
			case '\t':
				break;
			default:
				if (myBuffer == eCurrentBuffer::InputField)
				{
					myInputFieldBuffer[myInputFieldCounter++] = c;
				}
				else
				{
					myTagBuffer[myTagCounter++] = c;
				}
				break;
		}	
	}
	return result;
}

void DXMUI::DXMParser::Unparse(const std::wstring& aPath, const Canvas* aCanvas)
{
	//@TODO Read canvas and write to file.
}

void DXMUI::DXMParser::ParseTag(DXMBuilder& aBuilder)
{
	if (myTagBuffer[0] == '/')
	{
		AttachDataToBuilder(aBuilder);
	}
	else
	{
		switch (myTagBuffer[0])
		{
			case 't':
				myCurrentTag = eTagType::Text;
				break;
			case 'd':
				if(!memcmp(myTagBuffer, "div", 3)) myCurrentTag = eTagType::Div;
				else assert(true && "Incorrect tag");
				break;
			case 'i':
				if (!memcmp(myTagBuffer, "img", 3)) myCurrentTag = eTagType::Image;
				else assert(true && "Incorrect tag");
				break;
			case 'b':
				if(!memcmp(myTagBuffer, "button", 6)) myCurrentTag = eTagType::Button;
				else assert(true && "Incorrect tag");
				break;
			default:
				assert(true && "Incorrect tag");
				break;
		}
		char* id = strchr(myTagBuffer, ',') ;
		if (id != nullptr)
		{
			myCurrentIdentifier = std::string(id + 1);
		}
		else
		{
			myCurrentIdentifier = std::string();
		}
	}

	memset(myTagBuffer, '\0', 64);
	myTagCounter = 0;
}

void DXMUI::DXMParser::AttachDataToBuilder(DXMBuilder& aBuilder)
{
	switch (myCurrentTag)
	{
		case eTagType::Text:
			aBuilder.Append(myCurrentIdentifier,new TextElement(myInputFieldBuffer));
			break;
		case eTagType::Div:
			//aBuilder.Append(new DivElement(myInputFieldBuffer));
			break;
		case eTagType::Button:
			aBuilder.Append(myCurrentIdentifier, new ButtonElement(myInputFieldBuffer));
			break;
		case eTagType::Image:
			aBuilder.Append(myCurrentIdentifier, new ImageElement(myInputFieldBuffer));
			break;
		default:
			break;
	}
	memset(myInputFieldBuffer, '\0', 256);
	myInputFieldCounter = 0;
}
