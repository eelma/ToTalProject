#include "KDxState.h"
ID3D11SamplerState* KDxState::g_pDefaultSS=nullptr;
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

	hr=pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSS);
	return true;
}
bool KDxState::Release()
{
	if (g_pDefaultSS)g_pDefaultSS->Release();
	return true;
}