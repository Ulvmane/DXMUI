#include "DXMParser.h"
#include "Canvas\Elements\TextElement.h"

#include <assert.h>
#include <filesystem>
#include <fstream>

DXMUI::DXMParser::DXMParser()
{
	myReadCharacter = '\0';
	memset(myTagBuffer, '\0', 64);
	memset(myInputFieldBuffer, '\0', 256);
	myFunctionMap[eCurrentBuffer::InputField] = [&]() { myInputFieldBuffer[myCounter++] = myReadCharacter; };
	myFunctionMap[eCurrentBuffer::Tag] = [&]() { myTagBuffer[myCounter++] = myReadCharacter; };
}

DXMUI::DXMBuilder DXMUI::DXMParser::Parse(const std::wstring& aPath)
{
	DXMBuilder result;
	
	assert(std::filesystem::exists(aPath) && "Specified path does not exist");
	
	std::ifstream input;
	input.open(aPath);

	if (input.is_open())
	{
		while (!input.eof())
		{
			myReadCharacter = input.get();
			switch (myReadCharacter)
			{
				case '<':
					// Todo begin read tag.
					myBuffer = eCurrentBuffer::Tag;
					break;
				case '>':
					ParseTag(result);
					myBuffer = eCurrentBuffer::InputField;
					memset(myTagBuffer, '\0', 64);
					break;
				case ' ':
				case '\n':
				case '\t':
					//Discard linechanges and blankspace
					break;
				default:
					myFunctionMap[myBuffer]();
					break;
			}
		}
	}
	else
	{
		assert(true && "Input file invalid");
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
		myCurrentIdentifier = std::string(strchr(myTagBuffer, ','));
	}

	memset(myTagBuffer, '\0', 64);
}

void DXMUI::DXMParser::AttachDataToBuilder(DXMBuilder& aBuilder)
{
	switch (myCurrentTag)
	{
		case eTagType::Text:
			aBuilder.Append(new TextElement(myInputFieldBuffer));
			break;
		case eTagType::Div:
			//aBuilder.Append(new DivElement(myInputFieldBuffer));
			break;
		case eTagType::Button:
			//aBuilder.Append(new ButtonElement(myInputFieldBuffer));
			break;
		case eTagType::Image:
			//aBuilder.Append(new ImageElement(myInputFieldBuffer));
			break;
		default:
			break;
	}
	memset(myInputFieldBuffer, '\0', 256);
}
