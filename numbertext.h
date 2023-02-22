#pragma once
#include "gameObject.h"

class NumberText : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetNumber(int num);

	static void SetScoreNumSize(D3DXVECTOR2 size) {
		if (m_ScoreNumSize)
		{
			delete m_ScoreNumSize;
		}
		m_ScoreNumSize = new D3DXVECTOR2(size);
	}
	static void SetScoreNumColor(D3DXCOLOR color) {
		if (m_ScoreNumColor)
		{
			delete m_ScoreNumColor;
		}
		m_ScoreNumColor = new D3DXCOLOR(color);
	}

private:
	static const D3DXVECTOR2* m_ScoreNumSize;
	static const D3DXCOLOR* m_ScoreNumColor;

	class DrawSprite* m_drawSprite = nullptr;
};
