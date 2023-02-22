#pragma once
#include "gameObject.h"

class Box : public GameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
};