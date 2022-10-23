#include "KDxState.h"
ID3D11SamplerState* KDxState::g_pDefaultSSWrap=nullptr;
ID3D11SamplerState* KDxState::g_pDefaultSSMirror = nullptr;
ID3D11BlendState* KDxState::g_pDefaultBS = nullptr;

ID3D11RasterizerState* KDxState::g_pDefaultRSWireFrame=nullptr;
ID3D11RasterizerState* KDxState::g_pDefaultRSSolid=nullptr;

ID3D11DepthStencilState* KDxState::g_pDefaultDepthStencil = nullptr;
ID3D11DepthStencilState* KDxState::g_pGreaterDepthStencil = nullptr;
//���÷� ������Ʈ��� ���� �׻� ����ü�� ä���� �� ����ü�� ���ؼ� ��������� ������ �������ִ�
bool KDxState::SetState(ID3D11Device* pd3dDevice)
{
    HRESULT hr;

	D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.Filter=D3D11_FILTER_MIN_MAG_MIP_POINT;//�ֱ��� ���͸� ���� uv���� ���� ����� �ȼ��� �����ؼ� �ٿ���
    //x�� y�� z�� 0�� 1�� ��� �ؽ�Ʈ ��ǥ�� ����ҷ� ���� �����= 0-1 1-1 �ݺ�
    //0�� 1���̸� ����� 3�� ������ 3���� �򸰴�
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
    rd.FillMode = D3D11_FILL_WIREFRAME;//�ʸ��� ���̾������� �ָ���
    rd.CullMode = D3D11_CULL_NONE;//�ø��� �����̳� �޸��̳� �츮�� ������ �ð�����̴� �ո����� �ø��޸��� �Ѹ��� ����
    pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSWireFrame);
    rd.FillMode = D3D11_FILL_SOLID;//�ʸ��� ���̾������� �ָ���
    pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSSolid);//�ָ���� �������ִ�

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