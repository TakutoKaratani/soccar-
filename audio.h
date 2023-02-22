#pragma once

#include <xaudio2.h>
#include "gameObject.h"

class Audio : public GameObject
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;
	
	static const int SOURCE_VOICE_MAX = 20;
	IXAudio2SourceVoice*	m_SourceVoice[SOURCE_VOICE_MAX];
	BYTE*					m_SoundData;

	WAVEFORMATEX wfx = { 0 };


	int						m_Length;
	int						m_PlayLength;
	float					m_Volume;
	float					m_FadeVolume;
	float					m_Fadeadd;

	enum FADE
	{
		FADEIN,
		FADEOUT,
		NONE,
	};

	FADE m_state = FADE::NONE;


public:
	static void InitMaster();
	static void UninitMaster();

	void Init() { GameObject::Init(); }
	void Uninit();
	void Update();
	void Draw() { GameObject::Draw(); }

	void Load(const char *FileName);
	void Play(bool Loop = false);
	void Stop();
	void SetVolume(float vol) { m_Volume = vol; }
	void FadeVolume(float time, float vol);
	void FadeStop(float time);

};

