#pragma once
#include "gameObject.h"

class SoccerGoal : public GameObject
{
public:
	void Init() override;
	void Update() override;

	bool Goal() { return m_GoalFrag; }
	void Reset();
private:
	bool m_GoalFrag = false;
	class GoalParticle* m_ParticleSystem = nullptr;
};