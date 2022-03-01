#include <iostream>
#include "Parser\Markup\DXMParser.h"

#include <chrono>
#include <ctime>
#include <cmath>

using namespace DXMUI;

int main()
{
    DXMParser markupParser;
    auto clock_start = std::chrono::system_clock::now();
    DXMBuilder UIBuilder = markupParser.Parse(L"Test_Markup.DXMarkup");
    Canvas myCanvas = UIBuilder.Build();
    myCanvas.Render();
    auto clock_now = std::chrono::system_clock::now();
    auto elapsedTime = clock_now - clock_start;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(clock_now - clock_start).count() << "ms";
}
