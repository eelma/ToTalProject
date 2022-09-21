#pragma once
#include"KStd.h"
//샘플러 스테이트
class KDxState
{
public:
	static ID3D11SamplerState* g_pDefaultSS;
	static bool SetState(ID3D11Device* pd3dDevice);
	static bool Release();
};

