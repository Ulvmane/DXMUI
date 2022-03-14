#pragma once
#include "Canvas\IInteractableElement.h"
#include <string>
namespace DXMUI
{
    class ButtonElement :  public IInteractableElement
    {
    public:
        ~ButtonElement() = default;
        ButtonElement(const char* aText);
        virtual void Interact() override;
        virtual void Render() override;
        virtual void SetPosition(const float aX, const float aY) override;
    private:
        std::string myText;
    };
}

