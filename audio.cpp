
#include "main.h"
#include "audio.h"
#include <math.h>




IXAudio2*				Audio::m_Xaudio = NULL;
IXAudio2MasteringVoice*	Audio::m_MasteringVoice = NULL;


void Audio::InitMaster()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	XAudio2Create(&m_Xaudio, 0);

	m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);
}


void Audio::UninitMaster()
{
	m_MasteringVoice->DestroyVoice();
	m_Xaudio->Release();
	CoUninitialize();
}









void Audio::Load(const char *FileName)
{

	wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;


		hmmio = mmioOpen((LPSTR)FileName, &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);



		buflen = datachunkinfo.cksize;
		m_SoundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)m_SoundData, buflen);


		m_Length = readlen;
		m_PlayLength = readlen / wfx.nBlockAlign;


		mmioClose(hmmio, 0);
	}


	for (int i = 0; i < SOURCE_VOICE_MAX; i++)
	{
		m_Xaudio->CreateSourceVoice(&m_SourceVoice[i], &wfx);
	}
}


void Audio::Uninit()
{
	GameObject::Uninit();
	for (int i = 0; i < SOURCE_VOICE_MAX; i++)
	{
		m_SourceVoice[i]->Stop();
		m_SourceVoice[i]->DestroyVoice();
	}

	delete[] m_SoundData;
}

void Audio::Update()
{
	GameObject::Update();
	if (m_state == FADE::FADEIN)
	{
		m_FadeVolume += m_Fadeadd;
		if (m_FadeVolume >= m_Volume)
		{
			m_FadeVolume = m_Volume;
		}
	}
	if (m_state == FADE::FADEOUT)
	{
		m_Volume -= m_Fadeadd;
	}


	for (int i = 0; i < SOURCE_VOICE_MAX; i++)
	{
		if (m_state == FADE::FADEIN)
		{
			m_SourceVoice[i]->SetVolume(m_FadeVolume);
			if (m_FadeVolume >= m_Volume)
			{
				m_state = FADE::NONE;
			}
		}

		if (m_state == FADE::FADEOUT)
		{
			if (m_Volume > 0)
			{
				m_SourceVoice[i]->SetVolume(m_Volume);
			}
			else
			{
				Stop();
				m_state = FADE::NONE;
			}
		}
	}
	
}


void Audio::Play(bool Loop)
{
	for (int i = 0; i < SOURCE_VOICE_MAX; i++)
	{
		XAUDIO2_VOICE_STATE state;

		m_SourceVoice[i]->GetState(&state);

		if (state.BuffersQueued == 0)
		{
			XAUDIO2_BUFFER bufinfo;

			memset(&bufinfo, 0x00, sizeof(bufinfo));
			bufinfo.AudioBytes = m_Length;
			bufinfo.pAudioData = m_SoundData;
			bufinfo.PlayBegin = 0;
			bufinfo.PlayLength = m_PlayLength;

			if (Loop)
			{
				bufinfo.LoopBegin = 0;
				bufinfo.LoopLength = m_PlayLength;
				bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
			}

			m_SourceVoice[i]->SubmitSourceBuffer(&bufinfo, NULL);

			//float outputMatrix[4] = { 1.0f , 0.0f, 0.0f , 0.0f };
			//m_SourceVoice->SetOutputMatrix(m_MasteringVoice, 2, 2, outputMatrix);
			m_SourceVoice[i]->SetVolume(m_Volume);
			m_SourceVoice[i]->Start();
			break;
		}
	}

}

void Audio::Stop()
{

	for (int i = 0; i < SOURCE_VOICE_MAX; i++)
	{
		m_SourceVoice[i]->Stop();
		m_SourceVoice[i]->FlushSourceBuffers();
	}
}

void Audio::FadeVolume(float time, float vol)
{
	if (m_state != FADE::NONE) return;
	m_Volume = vol;
	m_state = FADE::FADEIN;
	m_FadeVolume = 0.0f;
	m_Fadeadd = m_Volume / time / 60.0f;
}

void Audio::FadeStop(float time)
{
	if (m_state != FADE::NONE) return;
	m_state = FADE::FADEOUT;
	m_Fadeadd = m_Volume / time / 60.0f;
}



