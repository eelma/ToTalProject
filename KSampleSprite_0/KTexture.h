#pragma once
#include"KStd.h"
class KTexture
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

public:
	ID3D11Texture2D* m_pTexture = nullptr;
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
	D3D11_TEXTURE2D_DESC m_Desc;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	HRESULT Load(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pImmediateContext,
		wstring filename);

};

