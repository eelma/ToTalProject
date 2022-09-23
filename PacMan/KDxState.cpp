#include "KDxState.h"
ID3D11SamplerState* KDxState::g_pDefaultSS=nullptr;
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

	hr=pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSS);
	return true;
}
bool KDxState::Release()
{
	if (g_pDefaultSS)g_pDefaultSS->Release();
	return true;
}