#include "Sample.h"

void KUser2D::SetRect(KRect rt)
{
    m_rt = rt;
}
//vPos(ȭ�� ��ǥ)�� ndc ��ǥ�� ����(������)�ؾ��Ѵ�
//ȭ�� ��ǥ�� �����ϰ� ���������� ndc�� ���������Ѵ�
//ndc��ǥ�� ������ִ� ����� �ʿ��ϴ�
void KUser2D::SetPosition(KVector2D vPos)
{
    KVector2D pos = vPos;
    //0~800 -> 0~1-> -1~+1
    pos.x = (vPos.x / g_rtClient.right)*2.0f-1.0f;
    pos.y = (vPos.y / g_rtClient.bottom) * 2.0f - 1.0f;
}


bool	Sample::Init()
{
    
   
    //map
    /*KBaseObject* pObjectMap = new KBaseObject;    
    pObjectMap->Create(m_pd3dDevice, m_pImmediateContext,    
        L"../../data/KGCABK.bmp",    
        L"../../data/shader/DefaultShape.txt");    
    m_pObjectList.push_back(pObjectMap);*/


    //user character
    //{90,1,40,60} player �̹��� ����,{400,300}ȭ�� ��ũ�� ��ǥ ���ؽ� ���۰� ����������Ѵ�
    //-1~+1�� ���� ����� ���������
    //create �ϸ� -1~1�� ���ؽ� ���۰� ��������� �� ������ ������Ʈ�� Ǫ����
    m_pUser = new KUser2D;
    m_pUser->Create(m_pd3dDevice, m_pImmediateContext,
        L"../../data/bitmap1.bmp",
        L"../../data/shader/DefaultShape.txt");
    m_pUser->SetRect({ 90,1,40,60 });
    m_pUser->SetPosition({ (float)g_rtClient.right/2,(float)g_rtClient.bottom/2 });


    
    return true;
}
bool		Sample::Frame()
{
    for (auto obj : m_pObjectList)
    {
        obj->Frame();
    }
    return true;
}
bool		Sample::Render()
{
    
    for (auto obj : m_pObjectList)
    {
        obj->Render();
    }
   
    return true;
}
bool		Sample::Release()
{
    for (auto obj : m_pObjectList)
    {
        obj->Release();
        delete obj;
    }
    return true;
}


GAME_RUN(KSampleSprite_0, 1024, 768)
