#pragma once
#include "gameObject.h"
class Sprite : public GameObject
{
public:
	void Init() override;

	class DrawSprite* GetDrawSprite() { return m_drawSprite; }
private:
	class DrawSprite* m_drawSprite = nullptr;
};

