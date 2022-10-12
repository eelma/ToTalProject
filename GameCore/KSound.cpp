#include "KSound.h"
#include <tchar.h>
bool		KSound::Load(FMOD::System* pSystem,
	wstring filename)
{
	m_pSystem = pSystem;
	FMOD_RESULT hr = m_pSystem->createSound(
		to_wm(filename).c_str(),
		FMOD_DEFAULT, nullptr,
		&m_pSound);
	if (hr == FMOD_OK)
	{
		m_pSound->getLength(&m_TotalTime, FMOD_TIMEUNIT_MS);
	}
	return false;
}
bool KSound::Init()
{
	return true;
}
bool		KSound::PlayEffect(bool bLoop)
{
	FMOD_RESULT hr =
		m_pSystem->playSound(m_pSound, nullptr, false,
			&m_pChannel);
	if (hr == FMOD_OK)
	{
		m_fVolume = 0.3f;
		m_pChannel->setVolume(m_fVolume);
		SetLoop(bLoop);
	}
	return true;
}
bool		KSound::PlayEffect2(bool bLoop)
{
	bool playing = false;
	m_pChannel->isPlaying(&playing);
	if(!playing){
	FMOD_RESULT hr =
		m_pSystem->playSound(m_pSound, nullptr, false,
			&m_pChannel);
	if (hr == FMOD_OK)
	{
		m_fVolume = 0.5f;
		m_pChannel->setVolume(m_fVolume);
		SetLoop(bLoop);
		
	}
	return true;
	}
}
bool		KSound::Play(bool bLoop)
{
	if (IsPlay() == false)
	{
		FMOD_RESULT hr =
			m_pSystem->playSound(m_pSound, nullptr, false,
				&m_pChannel);
		if (hr == FMOD_OK)
		{
			m_fVolume = 0.5f;
			m_pChannel->setVolume(m_fVolume);
			SetLoop(bLoop);
		}
	}
	return true;
}
bool        KSound::IsPlay()
{
	bool playing = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&playing);
	}
	return playing;
}
void		KSound::SetLoop(bool bLoop)
{
	if (bLoop)
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	else
		m_pSound->setMode(FMOD_LOOP_OFF);
}
void		KSound::Stop()
{
	m_pChannel->stop();
}
void KSound::Paused()
{
	if (m_pChannel == nullptr) return;
	bool paused;
	m_pChannel->getPaused(&paused);
	m_pChannel->setPaused(!paused);
}
void KSound::VolumeUp(float fVolume)
{
	m_fVolume += fVolume;
	m_fVolume = min(1.0f, m_fVolume);
	m_pChannel->setVolume(m_fVolume);
}
void KSound::VolumeDown(float fVolume)
{
	m_fVolume -= fVolume;
	m_fVolume = max(0.0f, m_fVolume);
	m_pChannel->setVolume(m_fVolume);
}
bool KSound::Frame()
{
	return true;
}
bool KSound::Render()
{

	return true;
}
bool KSound::Release()
{
	if (m_pSound) m_pSound->release();
	
	return true;
}