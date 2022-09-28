#pragma once
#include "KSound.h"
#include "KStd.h"
class KSoundManager : public KSingleTone<KSoundManager>
{
	FMOD::System* m_pSystem = nullptr;
private:
	friend class KSingleTone<KSoundManager>;
	std::list<std::wstring>  m_fileList;
private:
	friend class KSingleTone<KSoundManager>;
	std::map<std::wstring, KSound*> m_List;
public:
	T_STR		GetSplitName(std::wstring name);
	void		LoadDir(std::wstring path);
	void		LoadAll(std::wstring path);
	bool	    Init();
	bool		Frame();
	KSound* Load(std::wstring filename);
	bool	    Release();
	KSound* GetPtr(W_STR name);
private:
	KSoundManager();
public:
	~KSoundManager();
};

#define I_Sound KSoundManager::GetInstance()
