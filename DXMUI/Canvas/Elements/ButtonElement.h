#pragma once
#include "Canvas\IInteractableElement.h"
#include "D3D11_Interface\DXMRenderText.h"
#include "D3D11_Interface\DXMDrawSurface.h"
#include <string>
#include <functional>

namespace DXMUI
{
    class ButtonElement :  public IInteractableElement
    {
    public:
        ~ButtonElement() = default;
        ButtonElement(const char* aText);
        virtual void Render() override;
        virtual void SetPosition(const float aX, const float aY) override;
        virtual Vector2 GetPosition() override;
    private:
        std::string myText;
        DXMRenderText myRenderText;
        DXMDrawSurface mySurface;
    };
}

