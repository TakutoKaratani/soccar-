#pragma once
#include "gameObject.h"

class BallAssist : public GameObject
{
public:
	void Init() override;
	void Update() override;

private:
	D3DXCOLOR color = { 1.0f,1.0f,1.0f,1.0f };

	GameObject* ball = nullptr;
	class DrawSprite* m_ds = nullptr;
};
