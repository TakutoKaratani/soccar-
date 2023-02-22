#pragma once
#include "gameObject.h"

class Sky : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	GameObject* m_pOrigin = nullptr;
	float m_frame = 0;
};

