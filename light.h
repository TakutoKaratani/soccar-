#pragma once
#include "gameObject.h"

class Light : public GameObject
{
public:
	virtual void Init() override;
	virtual void Uninit() override {}
	virtual void Update() override {}
	virtual void Draw() override {}

	virtual void SetLight();

	void SetAt(D3DXVECTOR3 at) { m_at = at; }

protected:
	LIGHT m_Light{};
	D3DXVECTOR3 m_at;
	float m_near, m_far;
};