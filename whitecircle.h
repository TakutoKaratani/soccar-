#pragma once
#include "gameObject.h"
class WhiteCircle : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};
