#pragma once
#include "gameObject.h"

class StaminaGauge : public GameObject
{
public:
	void Init() override;
	void Update() override;
private:
	class CarControl* m_cc;
	class DrawSprite* m_GaugeSprite;
	D3DXVECTOR3 m_DefaultScale = { 0.0f,0.0f,0.0f };
};