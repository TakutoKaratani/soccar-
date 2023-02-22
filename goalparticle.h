#pragma once
#include "particlesystem.h"

class GoalParticle : public ParticleSystem
{
public:
	GoalParticle(class GameObject* go) :ParticleSystem(go) {}

	void Init() override;
	void Active();
	void Reset() { on = false; }
private:
	int burstAmount = 0;
	bool on = false;
};
