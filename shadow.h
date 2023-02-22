#pragma once
#include "gameObject.h"
class Shadow : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
};

