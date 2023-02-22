#pragma once
#include "fadebase.h"
class FadeScrollSide : public FadeBase
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetSpeed(float speed) override {
		m_Speed = (SCREEN_WIDTH + m_delay) / speed / 60.0f;
	}

	void FadeIn() override {
		transform->m_Position.x = SCREEN_WIDTH;
		m_state = FADE_STATE::FADE_IN;
	}
	void FadeOut() override {
		transform->m_Position.x = 0.0f - m_delay * 0.5f;
		m_state = FADE_STATE::FADE_OUT;
	}

private:
	float m_delay = 0.0f;

	class DrawSprite* m_DrawSprite = nullptr;
};

