#pragma once
#include "KStd.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#pragma comment (lib,"DirectXTK.lib")
#ifdef _DEBUG
#pragma comment(lib, "DirectXTK_D.lib")
#else
#pragma comment(lib, "DirectXTK_R.lib")
#endif

class KTexture
{
public:
	ID3D11Texture2D* m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
	D3D11_TEXTURE2D_DESC		m_Desc;
public:
	HRESULT Load(ID3D11Device* pd3dDevice,// ?????̽? ??ü
		ID3D11DeviceContext* pImmediateContext, wstring name);
	void Apply(ID3D11DeviceContext* pImmediateContext,
		UINT iSlot = 0);
	bool Release();
};