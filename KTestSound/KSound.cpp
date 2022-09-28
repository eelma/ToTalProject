#include "KSound.h"
#include <tchar.h>
bool		KSound::Load(std::string filename)
{
	FMOD_RESULT hr = m_pSystem->createSound(
		filename.c_str(),
		FMOD_DEFAULT, nullptr,
		&m_pSound);
	if (hr == FMOD_OK)
	{
		m_pSound->getLength(&m_TotalTime, FMOD_TIMEUNIT_MS);
	}
	return true;
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
		m_fVolume = 0.5f;
		m_pChannel->setVolume(m_fVolume);
		SetLoop(bLoop);
	}
	return true;
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
	m_pSystem->update();
	if (m_pChannel)
	{
		unsigned int ms = 0;
		m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
		TCHAR szBuffer[256] = { 0, };
		_stprintf_s(szBuffer,
			_T("경과시간[%02d:%02d:%02d],파일크기[%02d:%02d:%02d]"),
			ms / 1000 / 60,
			ms / 1000 % 60,
			ms / 10 % 60,
			m_TotalTime / 1000 / 60,
			m_TotalTime / 1000 % 60,
			m_TotalTime / 10 % 60);
		m_szBuffer = szBuffer;
	}
	return true;
}
bool KSound::Render()
{

	return true;
}
bool KSound::Release()
{
	if (m_pSound) m_pSound->release();
	m_pSystem->close();
	m_pSystem->release();
	return true;
}