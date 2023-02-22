#pragma once
#include "gameObject.h"
class FadeBase : public GameObject
{
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void FadeIn() = 0;
	virtual void FadeOut() = 0;

	enum FADE_STATE
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT,
	};

	FADE_STATE GetFadeState() { return m_state; }
	virtual void SetSpeed(float speed)
	{
		if (speed == 0) return;
		if (speed < 0)speed *= -1.0f;
		m_Speed = speed;
	}

protected:
	float m_Speed = 0.01f;

	FADE_STATE m_state = FADE_STATE::FADE_NONE;
};

