#include "Sample.h"

bool Sample::GameDataLoad(const TCHAR* pszLoad)
{
	TCHAR pBuffer[256] = { 0 };
	TCHAR pTemp[256] = { 0 };

	int iNumSprite = 0;
	FILE* fp_src;
	_wfopen_s(&fp_src, pszLoad, _T("rt"));
	if (fp_src == NULL) return false;
	//파일 하나 읽어들인 다음

	
	_fgetts(pBuffer, _countof(pBuffer), fp_src);//스프라이트가 몇개인지 읽어준다
	_stscanf_s(pBuffer, _T("%s%d%s"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
	m_rtSpriteList.resize(iNumSprite);//그만큼 스프라이트를리사이즈한다

	for (int iCnt = 0; iCnt < iNumSprite; iCnt++)//스프라이트 갯수만큼 읽어들여서
	{
		int iNumFrame = 0;
		_fgetts(pBuffer, _countof(pBuffer), fp_src);
		_stscanf_s(pBuffer, _T("%s %d"), pTemp, (unsigned int)_countof(pTemp), &iNumFrame);
		//m_rtSpriteList[iCnt].resize(iNumFrame);

		RECT rt;
		for (int iFrame = 0; iFrame < iNumFrame; iFrame++)//프레임개수만큼 데이터를 읽어서 저장
		{
			_fgetts(pBuffer, _countof(pBuffer), fp_src);
			_stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
				&rt.left, &rt.top, &rt.right, &rt.bottom);
			m_rtSpriteList[iCnt].push_back(rt);
		}
	}
	fclose(fp_src);
	return true;
}
bool Sample::Init()
{
	GameDataLoad(L"SpriteInfo.txt");
	
	std::wstring shaderfilename = L"../../data/shader/DefaultShapeMask.txt";
	std::wstring mapShader = L"../../data/shader/DefaultShape.txt";
	KTexture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");


	m_pMap = new KMapObject;
	m_pMap->Create(m_pd3dDevice,
		m_pImmediateContext,
		mapShader,
		L"../../data/kgcabk.bmp");//"L"../../data/gameHeight.png");
	m_pMap->SetRect({ 0, 0,	2000.0f,2000.0f });
	m_pMap->SetPosition({ 0.0f, 0.0f });

	m_pObject = new KSprite;
	m_pObject->Create(m_pd3dDevice,
		m_pImmediateContext,
		shaderfilename,
		L"../../data/bitmap1.bmp");
	m_pObject->SetMask(pMaskTex);
	m_pObject->m_fSpeed = 300.0f;
	RECT rt = m_rtSpriteList[0][0];
	KRect kRt;
	kRt.x1 = rt.left;
	kRt.y1 = rt.top;
	kRt.w = rt.right;
	kRt.h = rt.bottom;
	m_pObject->SetRect(kRt);
	m_pObject->SetPosition({ 400,300 });



	m_pUser = new KUser2D;
	m_pUser->Create(m_pd3dDevice, m_pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/bitmap1.bmp");
	m_pUser->SetMask(pMaskTex);
	m_pUser->m_fSpeed = 300.0f;
	m_pUser->SetRect({ 91, 2, 39, 59 });
	m_pUser->SetPosition({ 400,300 });

	m_vCamera = m_pUser->m_vPos;
	return true;
}
bool Sample::Frame()
{
	m_pMap->SetCameraSize({ 800, 800 });
	m_pMap->SetCameraPos(m_vCamera);
	m_pMap->Frame();

	m_pUser->SetCameraSize({ 800, 800 });
	m_pUser->SetCameraPos(m_vCamera);
	m_pUser->Frame();//유저 프레임 연산 했고
	//m_vCamera = m_pUser->m_vPos;//카메라의 위치를 초기에는 유저의 위치로 세팅 항상 정가운데 있음

	static int iSpriteIndex = 1;
	if (I_Input.GetKey('1') == KEY_PUSH)
	{
		iSpriteIndex++;
		if (iSpriteIndex > 2) iSpriteIndex = 0;
	}
	static float eFffectRunning = 1.33f;
	static UINT index = 0;
	static float fEffectTimer = 0.0f;
	fEffectTimer += g_fSecondPerFrame;
	float fStep = eFffectRunning / (float)m_rtSpriteList[iSpriteIndex].size();
	if (fEffectTimer >= fStep)
	{
		fEffectTimer -= fStep;
		index++;
	}

	if (index >= m_rtSpriteList[iSpriteIndex].size())
	{
		index = 0;
	}//인덱스가 스프라이트를 지나면 다시 0
	RECT rt = m_rtSpriteList[iSpriteIndex][index];
	KRect kRt;
	kRt.x1 = rt.left;
	kRt.y1 = rt.top;
	kRt.w = rt.right;
	kRt.h = rt.bottom;
	m_pObject->SetRect(kRt);
	m_pObject->SetPosition({ (float)I_Input.m_ptPos.x,(float)I_Input.m_ptPos.y });//얘가 들어가야 버텍스 버퍼 변경
	
	
	return true;
}
bool Sample::Render()
{
	if (I_Input.GetKey('V') == KEY_HOLD)
	{
		m_pImmediateContext->RSSetState(KDxState::g_pDefaultRsWireFrame);
	}
	m_pMap->Render();//마스크 안쓰니까 그냥 렌더

	m_pUser->PreRender();
	m_pImmediateContext->PSSetShaderResources(1, 1,
		&m_pUser->m_pMaskTex->m_pTextureSRV);
	m_pUser->PostRender();

	m_pObject->PreRender();
	m_pImmediateContext->PSSetShaderResources(1, 1,
		&m_pObject->m_pMaskTex->m_pTextureSRV);
	m_pObject->PostRender();
	return true;
}
bool Sample::Release()
{
	m_pMap->Release();
	delete m_pUser;
	m_pMap = nullptr;

	m_pUser->Release();
	delete m_pUser;
	m_pUser = nullptr;

	m_pObject->Release();
	delete m_pObject;
	m_pObject = nullptr;
	return true;
}

GAME_RUN(KTestTexture, 800, 600)