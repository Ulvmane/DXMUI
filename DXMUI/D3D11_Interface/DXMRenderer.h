#pragma once
#include <vector>
#include "DXMDrawSurface.h"
#include "DXMTextRenderer.h"

struct	ID3D11DeviceContext;
struct	ID3D11Buffer;
class	ID3D11Device;
class	ID3D11SamplerState;
class	ID3D11BlendState;
namespace DXMUI
{
	class DXMRenderer
	{
	public:
		DXMRenderer();
		~DXMRenderer();
		void Render(ID3D11DeviceContext* aContext);
		bool Init(ID3D11Device* aDevice);
		static void AddDrawSurface(DXMDrawSurface& aSurface);
	private:
		static std::vector<DXMDrawSurface> ourDrawSurfaces;
		void SetShaders(ID3D11DeviceContext* aContext);
		void SetBuffer(ID3D11DeviceContext* aContext, DXMDrawSurface& aSurface);
		void SetSamplers(ID3D11DeviceContext* aContext);
		void SetBlendState(ID3D11DeviceContext* aContext);

		//void SetBuffer(ID3D11DeviceContext* aContext, DXMDrawSurface& aSurface);
		void ReSetSamplers(ID3D11DeviceContext* aContext);
		void ReSetBlendState(ID3D11DeviceContext* aContext);
		void ReSetShaders(ID3D11DeviceContext* aContext);
		DXMTextRenderer myTextRenderer;
		ID3D11Buffer* myElementBuffer		= nullptr;
		ID3D11Buffer* myVertexBuffer		= nullptr;
		ID3D11SamplerState* mySamplerState	= nullptr;
		ID3D11BlendState* myBlendState		= nullptr;
	};
}

