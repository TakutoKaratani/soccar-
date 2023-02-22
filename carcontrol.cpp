#include "main.h"
#include "carcontrol.h"
#include "gameObject.h"
#include "rigidbody.h"
#include "turboparticle.h"
#include "tool.h"

void CarControl::Init()
{
	m_rb = gameObject->GetComponent<Rigidbody>();
	if (m_rb == nullptr) this->SetDestroy();
	m_DefDrag = m_rb->GetDrag();
	m_CU = new CarControl::CarUpdate();
	m_CUtmp = nullptr;

	m_Speed = 6.0f;
	m_TurboScale = 1.5f;
	m_JumpPower = 1.0f;
	m_Angle = 0.05f;
	m_StaminaMax = 150.0f;
	m_TurboStamina = m_StaminaMax;
	m_StaminaConsumption = 1.0f;
	m_StaminaRecovery = 0.8f;

	m_Axel = false;
	m_Turbo = false;
	m_StaminaEmpty = false;
	m_Back = false;
	m_RightTurn = false;
	m_LeftTurn = false;
	m_IsGround = true;
}

void CarControl::Uninit()
{
	delete m_CU;
	if (m_CUtmp) delete m_CUtmp;
}

void CarControl::Update()
{
	m_CU->Update(this);
	if (!m_Turbo || m_StaminaEmpty)
	{
		m_TurboStamina += m_StaminaRecovery;
		if (m_TurboStamina > m_StaminaMax) m_TurboStamina = m_StaminaMax;
		if (!m_Turbo) m_StaminaEmpty = false;
	}

	m_Turbo = false;

	if (m_CUtmp)
	{
		delete m_CU;
		m_CU = m_CUtmp;
		m_CUtmp = nullptr;
	}
}

void CarControl::Axel()
{
	m_Axel = true;
}

void CarControl::Turbo()
{
	m_Turbo = true;
}

void CarControl::Back()
{
	m_Back = true;
}

void CarControl::RightTurn()
{
	m_RightTurn = true;
}

void CarControl::LeftTurn()
{
	m_LeftTurn = true;
}

void CarControl::Turn(D3DXVECTOR3 axis ,float angle)
{
	gameObject->GetTransform()->MulQuaternion(axis, angle);
}

void CarControl::Jump()
{
	m_CU->Jump(this);
}

void CarControl::Landing()
{
	if (m_IsGround) return;

	m_IsGround = true;
	m_rb->SetDrag(m_DefDrag);

	ChangeState(CarState::Landing);
}

void CarControl::ChangeState(CarState state)
{
	switch (state)
	{
	case CarState::Ground:
		m_CUtmp = new CarControl::CarUpdate();
		break;
	case CarState::Sky:
		m_CUtmp = new CarControl::CarSkyUpdate();
		break;
	case CarState::Landing:
		m_CUtmp = new CarControl::CarLandingUpdate();
		break;
	}
}


// ’Êí------------------------------------------------------------------------------
void CarControl::CarUpdate::Update(CarControl* cc)
{
	if (cc->m_Axel || cc->m_Turbo)
	{
		cc->m_Axel = false;
		float turboScale = 1.0f;
		if (cc->m_Turbo && !cc->m_StaminaEmpty)
		{
			turboScale = cc->m_TurboScale;
			cc->m_TurboStamina -= cc->m_StaminaConsumption;
			TurboParticle* tp = cc->gameObject->GetComponent<TurboParticle>();
			if (tp) tp->Active();
			if (cc->m_TurboStamina < 0)
			{
				cc->m_StaminaEmpty = true;
				cc->m_TurboStamina = 0;
			}
		}

		if (cc->m_RightTurn)
		{
			cc->Turn(Transform::up,cc->m_Angle);
			cc->m_RightTurn = false;
		}
		if (cc->m_LeftTurn)
		{
			cc->Turn(Transform::up, -cc->m_Angle);
			cc->m_LeftTurn = false;
		}

		cc->m_rb->AddForce(cc->gameObject->GetForward() * cc->m_Speed * turboScale, ForceMode::Force);

	}

	if (cc->m_Back && !cc->m_Turbo)
	{
		cc->m_Back = false;
		if (cc->m_RightTurn)
		{
			cc->Turn(Transform::up,-cc->m_Angle);
			cc->m_RightTurn = false;
		}
		if (cc->m_LeftTurn)
		{
			cc->Turn(Transform::up,cc->m_Angle);
			cc->m_LeftTurn = false;
		}

		cc->m_rb->AddForce(-cc->gameObject->GetForward() * cc->m_Speed, ForceMode::Force);
	}
}

void CarControl::CarUpdate::Jump(CarControl* cc)
{
	cc->m_IsGround = false;
	cc->m_rb->AddForce(Transform::up * cc->m_JumpPower, ForceMode::Impulse);
	cc->m_rb->SetDrag(cc->m_DefDrag);
	cc->ChangeState(CarState::Sky);
}


// ‹ó’†------------------------------------------------------------------------------
void CarControl::CarSkyUpdate::Update(CarControl* cc)
{
	if (cc->m_Axel)
	{
		cc->Turn(cc->gameObject->GetRight(), cc->m_Angle * 0.3f);
		cc->m_Axel = false;

		if (jumpTrigger)
		{
			jumpTrigger = false;
			Dodge(cc, cc->gameObject->GetForward());
		}
	}
	if (cc->m_Back)
	{
		cc->Turn(cc->gameObject->GetRight(), -cc->m_Angle * 0.5f);
		cc->m_Back = false;
		if (jumpTrigger)
		{
			jumpTrigger = false;
			Dodge(cc, -cc->gameObject->GetForward());
		}
	}
	if (cc->m_RightTurn)
	{
		cc->Turn(cc->gameObject->GetUp(), cc->m_Angle * 0.5f);
		cc->m_RightTurn = false;
		if (jumpTrigger)
		{
			jumpTrigger = false;
			Dodge(cc, cc->gameObject->GetRight());
		}
	}
	if (cc->m_LeftTurn)
	{
		cc->Turn(cc->gameObject->GetUp(), -cc->m_Angle * 0.5f);
		cc->m_LeftTurn = false;
		if (jumpTrigger)
		{
			jumpTrigger = false;
			Dodge(cc, -cc->gameObject->GetRight());
		}
	}

	if (jumpTrigger)
	{
		jumpTrigger = false;
		cc->m_rb->AddForce(Transform::up * cc->m_JumpPower, ForceMode::Impulse);
	}

	if (cc->m_Turbo && !cc->m_StaminaEmpty)
	{
		cc->m_TurboStamina -= cc->m_StaminaConsumption;
		TurboParticle* tp = cc->gameObject->GetComponent<TurboParticle>();
		if (tp) tp->Active();
		if (cc->m_TurboStamina < 0)
		{
			cc->m_StaminaEmpty = true;
			cc->m_TurboStamina = 0;
		}
		cc->m_rb->AddForce(cc->gameObject->GetForward()* cc->m_Speed * cc->m_TurboScale * 0.7f, ForceMode::Acceleration);
	}
}

void CarControl::CarSkyUpdate::Jump(CarControl* cc)
{
	if (!doubleJump) return;
	cc->m_rb->SetDrag(cc->m_DefDrag);
	doubleJump = false;
	jumpTrigger = true;
}

void CarControl::CarSkyUpdate::Dodge(CarControl* cc,D3DXVECTOR3 axis)
{
	axis.y = 0;
	cc->m_rb->AddForce(Tool::Vec3Normalize(Tool::Vec3Normalize(axis) + Transform::up) * cc->m_JumpPower * 2, ForceMode::Impulse);
}


// ’…’n------------------------------------------------------------------------------
void CarControl::CarLandingUpdate::Update(CarControl* cc)
{
	D3DXVECTOR3 forward = cc->gameObject->GetForward();
	forward.y = 0.0f;

	int n = 1; 
	if (Tool::Vec3Dot(forward, Transform::right) < 0) n *= -1;

	float rad = Tool::Vec3Angle(Transform::forward,forward);

	cc->gameObject->SetRotate(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	cc->gameObject->MulQuaternion(Transform::up, rad * n);
	cc->ChangeState(CarState::Ground);
}