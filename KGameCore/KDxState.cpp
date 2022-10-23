#include "KDxState.h"
ID3D11SamplerState* KDxState::g_pDefaultSSWrap=nullptr;
ID3D11SamplerState* KDxState::g_pDefaultSSMirror = nullptr;
ID3D11BlendState* KDxState::g_pDefaultBS = nullptr;

ID3D11RasterizerState* KDxState::g_pDefaultRSWireFrame=nullptr;
ID3D11RasterizerState* KDxState::g_pDefaultRSSolid=nullptr;

ID3D11DepthStencilState* KDxState::g_pDefaultDepthStencil = nullptr;
ID3D11DepthStencilState* KDxState::g_pGreaterDepthStencil = nullptr;
//샘플러 스테이트라는 것은 항상 구조체를 채워서 그 구조체에 의해서 만들어지는 과정을 가지고있다
bool KDxState::SetState(ID3D11Device* pd3dDevice)
{
    HRESULT hr;

	D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.Filter=D3D11_FILTER_MIN_MAG_MIP_POINT;//최근점 필터링 현재 uv값에 가장 가까운 픽셀을 선택해서 붙여라
    //x값 y값 z값 0과 1이 벗어난 텍스트 좌표를 어떻게할래 랩을 씌운다= 0-1 1-1 반복
    //0과 1사이를 벗어나서 3을 넣으면 3장이 깔린다
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    /*sd.MipLODBias;
    sd.MaxAnisotropy;
    sd.ComparisonFunc;
    sd.BorderColor[4];
    sd.MinLOD;
    sd.MaxLOD;*/

	hr=pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSSWrap);

    sd.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
    hr = pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSSMirror);


    D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(rd));
    rd.DepthClipEnable=true;
    rd.FillMode = D3D11_FILL_WIREFRAME;//필모드는 와이어프레임 솔리드
    rd.CullMode = D3D11_CULL_NONE;//컬모드는 정면이냐 뒷면이냐 우리는 무조건 시계방향이니 앞면으로 컬링뒷면은 뿌리지 말라
    pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSWireFrame);
    rd.FillMode = D3D11_FILL_SOLID;//필모드는 와이어프레임 솔리드
    pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSSolid);//솔리드는 가득차있다

    D3D11_DEPTH_STENCIL_DESC dsd;
    ZeroMemory(&dsd, sizeof(dsd));
    dsd.DepthEnable = TRUE;
    dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsd.DepthFunc = D3D11_COMPARISON_GREATER;
    hr = pd3dDevice->CreateDepthStencilState(&dsd, &g_pGreaterDepthStencil);

	return true;
}
bool KDxState::Release()
{
	if (g_pDefaultSSMirror)g_pDefaultSSMirror->Release();
    if (g_pDefaultSSWrap)g_pDefaultSSWrap->Release();
    if (g_pDefaultRSWireFrame)g_pDefaultRSWireFrame->Release();
    if (g_pDefaultRSSolid)g_pDefaultRSSolid->Release();
    if (g_pDefaultDepthStencil)g_pDefaultDepthStencil->Release();
    if (g_pGreaterDepthStencil)g_pGreaterDepthStencil->Release();
	return true;
}