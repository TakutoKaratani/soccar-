#pragma once
#include "component.h"

class EnemyAI : public Component
{
public:
	EnemyAI(class GameObject* go):Component(go){}

	void Init() override;
	void Uninit() override;
	void Update() override;
private:
	class CarControl* m_CarControl = nullptr;
	class GameObject* ball = nullptr;

	class State
	{
	public:
		virtual void Update(EnemyAI* ai) = 0;

	protected:
		D3DXVECTOR3 BallDistance(EnemyAI* ai);
		float BallSearch(EnemyAI* ai);

		const float BallSearchAngle = 10.0f;
	};

	class BallInstanceState : public State
	{
	public:
		void Update(EnemyAI* ai) override;
	};

	class TurnState : public State
	{
	public:
		void Update(EnemyAI* ai) override;
	};

	class AxelState :public State
	{
	public:
		void Update(EnemyAI* ai) override;
	};

	class ShootState :public State
	{
	public:
		ShootState();
		void Update(EnemyAI* ai) override;
	private:
		class Timer* timer = nullptr;
	};

	State* AIState = nullptr;
};