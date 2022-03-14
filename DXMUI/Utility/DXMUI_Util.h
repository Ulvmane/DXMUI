#pragma once
#include <memory>
template <class T> void DXM_SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}