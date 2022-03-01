#pragma once
#include "Canvas\IInteractableElement.h"
#include <string>
namespace DXMUI
{
    class ButtonElement :  public IInteractableElement
    {
    public:
        ButtonElement(const char* aText);
        virtual void Interact() override;
        virtual void Render() override;
    private:
        std::string myText;
    };
}

