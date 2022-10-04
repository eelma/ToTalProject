#include "KSprite.h"
HRESULT KSprite::Load(ID3D11Device* pd3dDevice,// 디바이스 객체
	ID3D11DeviceContext* pImmediateContext, wstring name)
{
	wstring shaderfilename = L"../../data/shader/DefaultShapeMask.txt";
	wstring mapshader = L"../../data/shader/DefaultShape.txt";
	KTexture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	Create(pd3dDevice,
		pImmediateContext,
		shaderfilename,
		L"../../data/bitmap1.bmp");
	SetMask(pMaskTex);
	m_fSpeed = 300.0f;
	return S_OK;
}