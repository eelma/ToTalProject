#pragma once
#include"KDevice.h"
#include"KInput.h"
#include"KTimer.h"
#include"KWriter.h"
#include "KSoundManager.h"
#include"KTextureManager.h"
#include"KShaderManager.h"
class KGameCore:public KDevice
{
public:
	ID3D11SamplerState* m_pDefaultSS=nullptr;

	KWriter m_Writer;
	bool bGameRun = true;
public:
	virtual bool		Init() { return true; }; // �ʱ�ȭ
	virtual bool		Frame() { return true; };// �ǽð� ���
	virtual bool		Render() { return true; };// �ǽð� ������
	virtual bool		Release() { return true; };// �Ҹ� �� ����

	//������Ʈ���� �ǵ��� ����� �����̺����� ����� ��������
private:
	bool		KCoreInit(); // �ʱ�ȭ
	bool		KCoreFrame();// �ǽð� ���
	bool		KCoreRender();// �ǽð� ������
	bool		KCorePreRender();
	bool		KCorePostRender();
	bool		KCoreRelease();// �Ҹ� �� ����	
public:
	bool		Run()override; // �Ҹ� �� ����	

};

