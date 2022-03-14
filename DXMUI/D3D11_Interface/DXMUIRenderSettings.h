#pragma once
#include <d3d11.h>
#include <string>

class DXMUIRenderSettings
{
public:
	friend class DXMRenderer;
	static bool Init(ID3D11Device* aDevice);
	static void Destroy();

	__forceinline static ID3D11InputLayout* GetLayout() { return ourInputLayout; }
	__forceinline static ID3D11PixelShader* GetPixelShader() { return ourPixelShader; };
	__forceinline static ID3D11VertexShader* GetVertexShader() { return ourVertexShader; };
	__forceinline static ID3D11GeometryShader* GetGeometryShader(){return ourGeometryShader;}
private:
	static bool LoadPixelShader(ID3D11Device* aDevice);
	static bool LoadVertexShader(ID3D11Device* aDevice);
	static bool LoadGeometryShader(ID3D11Device* aDevice);
	static bool InitInputLayout(ID3D11Device* aDevice, std::string& aVertexShaderData);
private:
	static ID3D11InputLayout* ourInputLayout;
	static ID3D11PixelShader* ourPixelShader;
	static ID3D11VertexShader* ourVertexShader;
	static ID3D11GeometryShader* ourGeometryShader;
};

