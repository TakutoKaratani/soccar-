#pragma once
#include "gameObject.h"
class TitleLogo : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	float u = 0;
	class DrawSprite* m_ds = nullptr;
};

