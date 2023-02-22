#pragma once
#include "gameObject.h"

class TitleCursor : public GameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	class TitleParticle* m_Particle[2]{};
};
