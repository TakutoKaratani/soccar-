#pragma once
#include "particlesystem.h"

class TitleParticle : public ParticleSystem
{
public:
	TitleParticle(class GameObject* go):ParticleSystem(go){}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetRadius(float r) { radius = r; }
	void SetDivide(int d) { divide = d; }

private:
	int divide = 1;
	float radius = 0.0f;
};