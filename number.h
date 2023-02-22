#pragma once
#include "gameObject.h"
#include "numbersprite.h"
#include <vector>

class Number : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	void SetNumber(int num);
	void SetMaxNum(int max) { 
		m_MaxNum = max;
		SetNumber(m_num);
	}
	void SetInterval(float interval) {
		m_Interval = interval;
		SetNumber(m_num);
	}
	void ZeroCover(bool f) { 
		m_ZeroCover = f;

		if (m_ss) delete m_ss;
		if (m_ZeroCover)
		{
			m_ss = new Number::SpriteSeterZeroCover();
		}
		else
		{
			m_ss = new Number::SpriteSeter();
		}

		SetNumber(m_num);
	}

	enum class MODE
	{
		LEFT,
		RIGHT
	};

	void SetMode(Number::MODE mode) { 
		m_mode = mode;
		SetNumber(m_num);
	}
private:
	int CheckDigit(int num);
	void Resize(int digit);
	void SetNumberSprite();

	void DestroySprite() {
		for (NumberSprite* ns : m_Sprite)
		{
			ns->SetDestroy();
		}
		m_Sprite.clear();
	}

	int m_num = 0;
	int m_MaxNum = 0;
	float m_Interval = 0;
	bool m_ZeroCover = false;
	Number::MODE m_mode = Number::MODE::LEFT;

	std::vector<NumberSprite*> m_Sprite;

	class SpriteSeter
	{
	public:
		virtual void SpriteSet(Number* Number);
	};

	class SpriteSeterZeroCover : public SpriteSeter
	{
		void SpriteSet(Number* Number) override;
	};

	SpriteSeter* m_ss = nullptr;
};
