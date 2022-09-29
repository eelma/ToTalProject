#include "KSoundManager.h"
#include <tchar.h>
#include <io.h>//_findclose
void	KSoundManager::LoadDir(std::wstring path)
{
    W_STR dirpath = path + L"*.*";
    intptr_t handle;
    struct _wfinddata_t fd;
    handle = _wfindfirst(dirpath.c_str(), &fd);
    if (handle == -1L) return;

    do {
        // 디렉토리 라면
        if ((fd.attrib & _A_SUBDIR)
            && fd.name[0] != '.')
        {
            LoadDir(path + fd.name + L"/");
        }
        else if (fd.name[0] != '.')
        {
            m_fileList.push_back(path + fd.name);
        }
    } while (_wfindnext(handle, &fd) == 0);
    _findclose(handle);
}
void	KSoundManager::LoadAll(std::wstring path)
{
    LoadDir(path);
    for (auto& data : m_fileList)
    {
        Load(data);
    }
}
KSound* KSoundManager::GetPtr(W_STR name)
{
    auto iter = m_List.find(name);
    if (iter != m_List.end())
    {
        KSound* pSound = iter->second;
        return pSound;
    }
    return nullptr;
}
bool KSoundManager::Init()
{
    FMOD::System_Create(&m_pSystem);
    m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
    return true;
}
W_STR KSoundManager::GetSplitName(std::wstring fullpath)
{
    W_STR name;
    TCHAR dirve[MAX_PATH] = { 0, };
    TCHAR dir[MAX_PATH] = { 0, };
    TCHAR filename[MAX_PATH] = { 0, };
    TCHAR ext[MAX_PATH] = { 0, };
    _tsplitpath_s(fullpath.c_str(),
        dirve, dir, filename, ext);
    name = filename;
    name += ext;
    return name;
}
KSound* KSoundManager::Load(std::wstring fullpath)
{
    HRESULT hr;
    // m_szName = 파일이름+확장자
    W_STR name = GetSplitName(fullpath);
    // 중복제거
    auto iter = m_List.find(name);
    if (iter != m_List.end())
    {
        return iter->second;
    }
    KSound* pNewData = new KSound;
    pNewData->m_szName = fullpath;
    if (pNewData)
    {
        hr = pNewData->Load(m_pSystem, fullpath);
        if (SUCCEEDED(hr))
        {
            m_List.insert(std::make_pair(name, pNewData));
        }
    }
    return pNewData;
}
bool KSoundManager::Frame()
{
    m_pSystem->update();
    for (auto data : m_List)
    {
        KSound* pData = data.second;
        if (pData) pData->Frame();
    }
    return true;
}
KSoundManager::KSoundManager()
{
}
bool KSoundManager::Release()
{
    for (auto data : m_List)
    {
        KSound* pData = data.second;
        if (pData) pData->Release();
        delete pData;
    }
    m_pSystem->close();
    m_pSystem->release();
    m_List.clear();
    return true;
}
KSoundManager::~KSoundManager()
{
    Release();
}