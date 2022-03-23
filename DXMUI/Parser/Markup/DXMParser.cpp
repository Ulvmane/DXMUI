#include "DXMParser.h"
#include "Canvas\Elements\TextElement.h"
#include "Canvas\Elements\ImageElement.h"
#include "Canvas\Elements\ButtonElement.h"
#include "Canvas\Elements\DivElement.h"
#include <assert.h>
#include <filesystem>
#include <fstream>
#include <sstream>

DXMUI::DXMParser::DXMParser()
{
	myDepth = 0;
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
				myTagBuffer = std::string();
				myBuffer = eCurrentBuffer::Tag;
				break;
			case '>':
				ParseTag(result);
				myBuffer = eCurrentBuffer::InputField;
				break;
			case '\n':
			case '\t':
			case '\0':
				break;
			default:
				if (myBuffer == eCurrentBuffer::InputField)
				{
					myContentStack.top() += c;
				}
				else
				{
					if(c != ' ')
						myTagBuffer += c;
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
		myDepth--;
		assert(myDepth >= 0 && "Parser error: To many endtags!");
	}
	else
	{
		switch (myTagBuffer[0])
		{
			case 't':
				myTypeStack.push(eTagType::Text);
				break;
			case 'd':
				if(myTagBuffer.compare(0,3,"div") == 0) myTypeStack.push(eTagType::Div);
				else assert(true && "Incorrect tag");
				break;
			case 'i':
				if ((myTagBuffer.compare(0,3, "img") == 0)) myTypeStack.push(eTagType::Image);
				else assert(true && "Incorrect tag");
				break;
			case 'b':
				if (myTagBuffer.compare(0, 6, "button") == 0) myTypeStack.push(eTagType::Button);
				else if (myTagBuffer.compare(0, 2, "br") == 0);
				else assert(true && "Incorrect tag");
				break;
			default:
				assert(true && "Incorrect tag");
				break;
		}
		if (myTagBuffer.compare(0, 2, "br") == 0)
		{
			myDepth--;
			myContentStack.top() += "\n";
		}
		else
		{
			myContentStack.push(std::string());
		}
		int idOffset = myTagBuffer.find_first_of(',');
		if (idOffset != std::string::npos)
		{
			myIDStack.push(std::string(myTagBuffer.begin() + idOffset + 1 , myTagBuffer.end()));
		}
		myDepth++;
	}
	myTagBuffer = std::string();
}

void DXMUI::DXMParser::AttachDataToBuilder(DXMBuilder& aBuilder)
{
	std::string inputBuffer = myContentStack.top();
	myContentStack.pop();

	switch (myTypeStack.top())
	{
		case eTagType::Text:
			AppendData(aBuilder, new TextElement(inputBuffer.c_str()));
			break;
		case eTagType::Div:
			AppendData(aBuilder, new DivElement());
			break;
		case eTagType::Button:
			AppendData(aBuilder, new ButtonElement(inputBuffer.c_str()));
			break;
		case eTagType::Image:
			AppendData(aBuilder, new ImageElement(inputBuffer.c_str()));
			break;
		default:
			break;
	}
	myTypeStack.pop();
	if (myTypeStack.empty()) aBuilder.AddNode();
}

void DXMUI::DXMParser::AppendData(DXMBuilder& aBuilder, ICanvasElement* aElement)
{
	auto id = myIDStack.empty() ? std::string() : myIDStack.top();
	aBuilder.DivAppend(myDepth, id, aElement);
	if(!myIDStack.empty())
		myIDStack.pop();
}