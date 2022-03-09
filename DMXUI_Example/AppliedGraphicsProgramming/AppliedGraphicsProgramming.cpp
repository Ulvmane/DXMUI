#include "framework.h"
#include "AppliedGraphicsProgramming.h"
#include "GraphicsEngine.h"

#include "Canvas\Canvas.h"
#include "Parser\Markup\DXMParser.h"
#include "Parser\Markup\MarkupBuilder.h"

//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPWSTR    lpCmdLine,
//                     _In_ int       nCmdShow)
//{
//    hInstance; hPrevInstance; lpCmdLine; nCmdShow;
//
//}

int main()
{

    CWindowHandler::SWindowData windowData;
    windowData.myX = 100;
    windowData.myY = 100;
    windowData.myWidth = 1280;
    windowData.myHeight = 720;

    CGraphicsEngine graphicsEngine;
    bool shouldRun = graphicsEngine.Init(windowData);

    MSG windowMessage = { 0 };

    DXMUI::Canvas myCanvas;
    DXMUI::DXMBuilder myBuilder;
    DXMUI::DXMParser myMarkupParser;

    myBuilder = myMarkupParser.Parse(L"Markup.DXMarkup");
    myCanvas = myBuilder.Build();
    myCanvas.Render();

    while (shouldRun)
    {
        while (PeekMessage(&windowMessage, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&windowMessage);
            DispatchMessage(&windowMessage);

            if (windowMessage.message == WM_QUIT)
            {
                shouldRun = false;
            }
        }


        graphicsEngine.BeginFrame();

        graphicsEngine.EndFrame();
    }
    return 0;
}