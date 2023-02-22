#pragma once
#include "fadebase.h"
class FadeAlpha : public FadeBase
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetSpeed(float speed)
	{
		m_Speed = 1.0f / speed / 60.0f;
	}

	void FadeIn() override {
		m_alpha = 0.0f;
		m_state = FADE_STATE::FADE_IN;
	}
	void FadeOut() override {
		m_alpha = 1.0f;
		m_state = FADE_STATE::FADE_OUT;
	}

private:
	float m_alpha = 0.0f;
	class DrawSprite* m_DrawSprite = nullptr;
};

