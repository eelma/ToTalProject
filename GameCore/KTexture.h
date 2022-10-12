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
<<<<<<< HEAD:GameCore/KTexture.h
	HRESULT Load(ID3D11Device* pd3dDevice,
=======
	HRESULT Load(ID3D11Device* pd3dDevice,// 디바이스 객체
>>>>>>> 48c3d63ff719d82e4eb39b8415a5f9bf170a0178:PacManCore/KTexture.h
		ID3D11DeviceContext* pImmediateContext, wstring name);
	void Apply(ID3D11DeviceContext* pImmediateContext,
		UINT iSlot = 0);
	bool Release();
};