#pragma once
#include "gameObject.h"

class NumberSprite : public GameObject
{
public:
	void Init() override;
	void Uninit() override;

	void SetSplit(int x, int y);
	void SetNumber(int num);

	class DrawSprite* GetDrawSprite() { return m_ds; }

private:
	class DrawSprite* m_ds = nullptr;
	int m_number = 0;

	const int* Split_X = nullptr;
	const int* Split_Y = nullptr;
};
