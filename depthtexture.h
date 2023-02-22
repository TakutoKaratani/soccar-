#pragma once
#include "gameobject.h"

class DepthTexture : public GameObject
{
public:
	void Init() override;
	void Update() override;

private:
	class DrawSprite* m_ds = nullptr;
};