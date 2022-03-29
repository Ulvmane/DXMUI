#include "framework.h"
#include "AppliedGraphicsProgramming.h"
#include "GraphicsEngine.h"

#include "Canvas\Canvas.h"
#include "Parser\Markup\DXMParser.h"
#include "Parser\Styles\DXSParser.h"
#include "Parser\Markup\MarkupBuilder.h"
#include "D3D11_Interface\DXM_D3D11_Interface.h"
#include <dxgidebug.h>


#define DEBUG_MEMORY
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

    DXMUI::Canvas* activeCanvas;
    DXMUI::Canvas myMain;
    DXMUI::Canvas myOptions;
    DXMUI::Canvas myCredits;

    DXMUI::DXMParser myMarkupParser;
    DXMUI::DXSParser myStyleParser;
    DXMUI::DXM_D3D11_Interface myInterface;

    CDirectX11Framework& framework = graphicsEngine.GetFramework();
    if (!myInterface.Init(graphicsEngine.GetHWND(), framework.myDevice, framework.myDeviceContext))
        return -1;
   

    myMain = myMarkupParser.Parse(L"Test_Markup.DXMarkup").Build();
    myMain.Init();
    myMain.ApplyStyle(myStyleParser.Parse(L"Test_Style.DXStyle"));

    myCredits = myMarkupParser.Parse(L"Credits.DXMarkup").Build();
    myCredits.Init();
    myCredits.ApplyStyle(myStyleParser.Parse(L"Test_Style.DXStyle"));

    myOptions = myMarkupParser.Parse(L"Options.DXMarkup").Build();
    myOptions.Init();
    myOptions.ApplyStyle(myStyleParser.Parse(L"Test_Style.DXStyle"));


    auto quit = [&]() { shouldRun = false; };
    auto returnToMain = [&]() { activeCanvas = &myMain; };
    myMain.SetCallback("quit", quit);
    myMain.SetCallback("options", [&]() { activeCanvas = &myOptions; });
    myMain.SetCallback("credits", [&]() { activeCanvas = &myCredits; });
    myCredits.SetCallback("back", returnToMain);
    myOptions.SetCallback("back", returnToMain);


    activeCanvas = &myMain;
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

        activeCanvas->Update();
        graphicsEngine.BeginFrame();
        myInterface.RenderCanvas(*activeCanvas);
        graphicsEngine.EndFrame();
    }
    

//#ifdef DEBUG_MEMORY
//
//    typedef HRESULT(__stdcall* fPtr)(const IID&, void**);
//    HMODULE hDll = GetModuleHandleW(L"dxgidebug.dll");
//    fPtr DXGIGetDebugInterface = (fPtr)GetProcAddress(hDll, "DXGIGetDebugInterface");
//    IDXGIDebug* pDxgiDebug;
//    DXGIGetDebugInterface(__uuidof(IDXGIDebug), (void**)&pDxgiDebug);
//    pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
//
//#endif // DEBUG_MEMORY

    return 0;
}