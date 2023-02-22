#pragma once
#include "gameObject.h"

class ScoreBord : public GameObject
{
public:
	void Init() override;
	void Update() override;

	void SetScore(int i, int score);
	void SetTime(int min, int sec);

private:
	class Number* m_Score[2] = { nullptr,nullptr };
	class Number* m_Min = nullptr;
	class Number* m_Sec = nullptr;
};
