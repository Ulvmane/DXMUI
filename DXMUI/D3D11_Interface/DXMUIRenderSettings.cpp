#include "DXMUIRenderSettings.h"
#include <fstream>
#include <assert.h>
#include "Utility\DXMUI_Util.h"

ID3D11InputLayout*    DXMUIRenderSettings::ourInputLayout;
ID3D11PixelShader*    DXMUIRenderSettings::ourPixelShader;
ID3D11VertexShader*   DXMUIRenderSettings::ourVertexShader;
ID3D11GeometryShader* DXMUIRenderSettings::ourGeometryShader;

bool DXMUIRenderSettings::Init(ID3D11Device* aDevice)
{
	if (!LoadPixelShader(aDevice))
		return false;

	if (!LoadVertexShader(aDevice))
		return false;

	if (!LoadGeometryShader(aDevice))
		return false;

    return true;
}

void DXMUIRenderSettings::Destroy()
{
	DXM_SafeRelease(&ourInputLayout);
	DXM_SafeRelease(&ourVertexShader);
	DXM_SafeRelease(&ourPixelShader);
	DXM_SafeRelease(&ourGeometryShader);
}

bool DXMUIRenderSettings::LoadPixelShader(ID3D11Device* aDevice)
{
	std::ifstream psFile;
	psFile.open("PS_DXMUI_SurfaceElement.cso", std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
	HRESULT result = aDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &ourPixelShader);
	psFile.close();
	
	if (!SUCCEEDED(result))
	{
		assert(false && "Error loading Pixel Shader");
		return false;
	}
    return true;
}

bool DXMUIRenderSettings::LoadVertexShader(ID3D11Device* aDevice)
{
	std::ifstream vsFile;
	vsFile.open("VS_DXMUI_SurfaceElement.cso", std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	HRESULT result = aDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &ourVertexShader);
	vsFile.close();

	if (!SUCCEEDED(result))
	{
		assert(false && "Error loading Vertex Shader");
		return false;
	}
	return InitInputLayout(aDevice, vsData);
}

bool DXMUIRenderSettings::LoadGeometryShader(ID3D11Device* aDevice)
{
	std::ifstream gsFile;
	gsFile.open("GS_DXMUI_SurfaceElement.cso", std::ios::binary);
	std::string gsData = { std::istreambuf_iterator<char>(gsFile), std::istreambuf_iterator<char>() };
	HRESULT result = aDevice->CreateGeometryShader(gsData.data(), gsData.size(), nullptr, &ourGeometryShader);
	gsFile.close();

	if (!SUCCEEDED(result))
	{
		assert(false && "Error loading Geometry Shader");
		return false;
	}
	return true;
}

bool DXMUIRenderSettings::InitInputLayout(ID3D11Device* aDevice, std::string& aVertexShaderData)
{
	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HRESULT result = aDevice->CreateInputLayout(inputLayoutDesc,
												sizeof(inputLayoutDesc) / sizeof(D3D11_INPUT_ELEMENT_DESC),
												aVertexShaderData.data(),
												aVertexShaderData.size(),
												&ourInputLayout);
	if (!SUCCEEDED(result))
	{
		assert(false && "Error loading Vertex Shader");
		return false;
	}
	return true;
}
