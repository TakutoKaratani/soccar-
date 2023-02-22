#include "main.h"
#include "manager.h"
#include "enemyAI.h"
#include "ball.h"
#include "carcontrol.h"
#include "tool.h"
#include "timer.h"

void EnemyAI::Init()
{
	m_CarControl = gameObject->GetComponent<CarControl>();
	if (m_CarControl == nullptr) this->SetDestroy();

	AIState = new EnemyAI::BallInstanceState();
}

void EnemyAI::Uninit()
{
	if (AIState) delete AIState;
}

void EnemyAI::Update()
{
	AIState->Update(this);
}

D3DXVECTOR3 EnemyAI::State::BallDistance(EnemyAI* ai)
{
	D3DXVECTOR3 dis = ai->ball->GetPosition() - ai->gameObject->GetPosition();
	dis.y = 0.0f;
	return dis;
}

float EnemyAI::State::BallSearch(EnemyAI* ai) 
{
	D3DXVECTOR3 forward = ai->gameObject->GetForward();
	forward.y = 0.0f;

	D3DXVECTOR3 ballDis = BallDistance(ai);

	return Tool::Vec3Angle(forward, ballDis, false);
}

void EnemyAI::BallInstanceState::Update(EnemyAI* ai)
{
	ai->ball = Manager::GetInstance()->GetScene()->GetGameObject<Ball>();
	if (ai->ball)
	{
		delete ai->AIState;
		ai->AIState = new EnemyAI::TurnState();
	}
}

void EnemyAI::TurnState::Update(EnemyAI* ai)
{
	float angle = BallSearch(ai);

	if (angle < BallSearchAngle)
	{
		delete ai->AIState;
		ai->AIState = new EnemyAI::AxelState();
	}
	else
	{
		float dot = Tool::Vec3Dot(ai->gameObject->GetRight(), Tool::Vec3Normalize(BallDistance(ai)));

		if (dot > 0)
		{
			ai->m_CarControl->Axel();
			ai->m_CarControl->RightTurn();
		}
		else
		{
			ai->m_CarControl->Axel();
			ai->m_CarControl->LeftTurn();
		}
	}
}

void EnemyAI::AxelState::Update(EnemyAI* ai)
{
	float angle = BallSearch(ai);

	if (angle < BallSearchAngle)
	{
		ai->m_CarControl->Axel();
		if (Tool::Vec3Length(BallDistance(ai)) < 15)
		{
			ai->m_CarControl->Turbo();
			if (Tool::Vec3Length(BallDistance(ai)) < 5)
			{
				ai->m_CarControl->Jump();
				delete ai->AIState;
				ai->AIState = new EnemyAI::ShootState();
			}
		}
	}
	else
	{
		delete ai->AIState;
		ai->AIState = new EnemyAI::TurnState();
	}
}

EnemyAI::ShootState::ShootState()
{
	timer = Manager::GetInstance()->GetScene()->AddGameObject<Timer>(0);
	timer->SetTime(0.5f);
	timer->Start();
}

void EnemyAI::ShootState::Update(EnemyAI* ai)
{
	ai->m_CarControl->Turbo();
	ai->m_CarControl->Back();
	if (timer->GetTime() <= 0)
	{
		timer->SetDestroy();
		delete ai->AIState;
		ai->AIState = new EnemyAI::TurnState();
	}
}