#pragma once
#include "light.h"

class GameLight : public Light
{
public:
	void Init() override;
	void SetLight() override;
private:
	D3DXVECTOR3 m_offset;
};