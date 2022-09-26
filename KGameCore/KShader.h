#pragma once
#include"KStd.h"
class KShader
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* m_pImmediateContext = nullptr;


	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3DBlob* m_pVSCode = nullptr;//버텍스셰이더 컴파일결과
	ID3DBlob* m_pPSCode = nullptr;//픽쉘셰이더 컴파일결과

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	HRESULT Load(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pImmediateContext,
		wstring filename);

};

