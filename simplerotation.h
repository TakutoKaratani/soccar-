#pragma once
#include "component.h"

class SimpleRotation : public Component
{
public:
	SimpleRotation(class GameObject* go)
		:Component(go) {}

	void Update();

	void SetSpeed(float speed) { m_speed = speed; }
	void SetAxis(D3DXVECTOR3 axis) { m_axis = axis; }

private:
	float m_speed = 0.1f;
	D3DXVECTOR3 m_axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
};
