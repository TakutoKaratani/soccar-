#pragma once
#include "gameObject.h"

class Enemy : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update()override;

	void PlayerCollision();

	void AIStop();
	void AIStart();

private:
	class Rigidbody* m_rb = nullptr;
	class EnemyAI* m_AI = nullptr;
};