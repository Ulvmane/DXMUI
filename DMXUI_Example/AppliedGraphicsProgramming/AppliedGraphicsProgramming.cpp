#include "framework.h"
#include "AppliedGraphicsProgramming.h"
#include "GraphicsEngine.h"

#include "Canvas\Canvas.h"
#include "Parser\Markup\DXMParser.h"
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

    DXMUI::Canvas myCanvas;
    DXMUI::DXMBuilder myBuilder;
    DXMUI::DXMParser myMarkupParser;

    DXMUI::DXM_D3D11_Interface myInterface;

    CDirectX11Framework& framework = graphicsEngine.GetFramework();
    if (!myInterface.Init(graphicsEngine.GetHWND(), framework.myDevice, framework.myDeviceContext))
        return -1;
   

    myBuilder = myMarkupParser.Parse(L"Test_Markup.DXMarkup");
    myCanvas = myBuilder.Build();
    myCanvas.Init();

    //myCanvas.SetCallback("callbackID_1", [&]() { printf("callbackID_1 was pressed \n"); });
    //myCanvas.SetCallback("callbackID_2", [&]() { printf("callbackID_2 was pressed \n"); });

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

        myCanvas.Update();
        graphicsEngine.BeginFrame();
        myInterface.RenderCanvas(myCanvas);
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