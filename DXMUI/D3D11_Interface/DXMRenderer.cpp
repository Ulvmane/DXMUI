#include "DXMRenderer.h"
#include "DXMUIRenderSettings.h"
#include <assert.h>
#include "Utility\DXMUI_Util.h"
std::vector< DXMUI::DXMDrawSurface> DXMUI::DXMRenderer::ourDrawSurfaces;

DXMUI::DXMRenderer::DXMRenderer()
{

}

DXMUI::DXMRenderer::~DXMRenderer()
{
	DXM_SafeRelease(&mySamplerState);
	DXM_SafeRelease(&myBlendState);
	DXM_SafeRelease(&myElementBuffer);
}

void DXMUI::DXMRenderer::Render(ID3D11DeviceContext* aContext)
{
	SetBlendState(aContext);
	SetSamplers(aContext);
	SetShaders(aContext);
	for (auto& drawSurface : ourDrawSurfaces)
	{
		SetBuffer(aContext, drawSurface);
		drawSurface.Render(aContext);
	}
	ourDrawSurfaces.clear();
}

bool DXMUI::DXMRenderer::Init(ID3D11Device* aDevice)
{
	D3D11_BUFFER_DESC bufferDescription = { 0 };
	bufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	bufferDescription.ByteWidth = sizeof(DXMDrawSurface::ElementBufferData);
	HRESULT result = aDevice->CreateBuffer(&bufferDescription, nullptr, &myElementBuffer);
	if (FAILED(result))
	{
		assert(false && "Failed creating draw surface buffer.");
		return false;
	}

	//Initialize Samplerstate
	D3D11_SAMPLER_DESC samplerDesc = {}; //Default Sampler
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = -FLT_MAX;
	samplerDesc.MaxLOD = FLT_MAX;
	result = aDevice->CreateSamplerState(&samplerDesc, &mySamplerState);
	assert(SUCCEEDED(result));

	D3D11_BLEND_DESC alphaBlendDesc = {};
	alphaBlendDesc.RenderTarget[0].BlendEnable = true;
	alphaBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	alphaBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	alphaBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	alphaBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	alphaBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	alphaBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
	alphaBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	result = aDevice->CreateBlendState(&alphaBlendDesc, &myBlendState);
	assert(SUCCEEDED(result));

	return true;
}

void DXMUI::DXMRenderer::AddDrawSurface(DXMDrawSurface& aSurface)
{
	ourDrawSurfaces.emplace_back(DXMDrawSurface(aSurface));
}

void DXMUI::DXMRenderer::SetShaders(ID3D11DeviceContext* aContext)
{
	aContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	aContext->IASetInputLayout(DXMUIRenderSettings::GetLayout());

	aContext->PSSetShader(DXMUIRenderSettings::GetPixelShader(), nullptr, 0);
	aContext->GSSetShader(DXMUIRenderSettings::GetGeometryShader(), nullptr, 0);
	aContext->VSSetShader(DXMUIRenderSettings::GetVertexShader(), nullptr, 0);
}

void DXMUI::DXMRenderer::SetBuffer(ID3D11DeviceContext* aContext, DXMDrawSurface& aSurface)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE bufferData;
	
	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = aContext->Map(myElementBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
	assert(SUCCEEDED(result));

	memcpy(bufferData.pData, &aSurface.myElementBufferData, sizeof(aSurface.myElementBufferData));
	aContext->Unmap(myElementBuffer, 0);
	aContext->GSSetConstantBuffers(0, 1, &myElementBuffer);
}

void DXMUI::DXMRenderer::SetSamplers(ID3D11DeviceContext* aContext)
{
	aContext->PSSetSamplers(0, 1, &mySamplerState);
}

void DXMUI::DXMRenderer::SetBlendState(ID3D11DeviceContext* aContext)
{
	aContext->OMSetBlendState(myBlendState, 0,0xffffffff);
}
