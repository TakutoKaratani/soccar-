#pragma once
#include "fadebase.h"
class FadeCurtain : public FadeBase
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetSpeed(float speed) override {
		m_Speed = (SCREEN_HEIGHT + m_delay) / speed / 60.0f;
	}

	void FadeIn() override {
		transform->m_Position.y = -SCREEN_HEIGHT - m_delay;
		m_state = FADE_STATE::FADE_IN;
	}
	void FadeOut() override {
		transform->m_Position.y = 0.0f + m_delay;
		m_state = FADE_STATE::FADE_OUT;
	}

private:
	float m_delay = 0.0f;

	class DrawSprite* m_DrawSprite = nullptr;
};

