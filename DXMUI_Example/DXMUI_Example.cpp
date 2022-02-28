#include <iostream>
#include "Parser\Markup\DXMParser.h"

using namespace DXMUI;

int main()
{
    DXMParser markupParser;
    DXMBuilder UIBuilder = markupParser.Parse(L"Test_Markup.DXMarkup");
    std::cout << "Hello World!\n";
}
