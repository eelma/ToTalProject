#pragma once
#include "KSound.h"
#include "KStd.h"
class KSoundManager : public KSingleTone<KSoundManager>
{
	FMOD::System* m_pSystem = nullptr;
private:
	friend class KSingleTone<KSoundManager>;
	list<wstring>  m_fileList;
private:
	friend class KSingleTone<KSoundManager>;
	map<wstring, KSound*> m_List;
public:
	T_STR		GetSplitName(wstring name);
	void		LoadDir(wstring path);
	void		LoadAll(wstring path);
	bool	    Init();
	bool		Frame();
	KSound* Load(wstring filename);
	bool	    Release();
	KSound* GetPtr(W_STR name);
private:
	KSoundManager();
public:
	~KSoundManager();
};

#define I_Sound KSoundManager::GetInstance()
