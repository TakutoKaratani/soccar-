#pragma once
#include "particlesystem.h"

class TurboParticle : public ParticleSystem
{
public:
	TurboParticle(class GameObject* go) :ParticleSystem(go) {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Active() { m_Active = true; }
private:
	bool m_Active = false;
};
