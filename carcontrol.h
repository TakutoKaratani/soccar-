#pragma once
#include "component.h"

class CarControl : public Component
{
public:
	CarControl(class GameObject* go) :Component(go) {}

	void Init() override;
	void Uninit() override;
	void Update() override;

	void Axel();
	void Turbo();
	void Back();
	void RightTurn();
	void LeftTurn();
	void Jump();
	void Landing();

	float GetStaminaRatio() 
	{ 
		if (m_StaminaMax == 0) return 0;
		return m_TurboStamina / m_StaminaMax; 
	}

private:
	void Turn(D3DXVECTOR3 axis, float angle);

	class Rigidbody* m_rb = nullptr;

	float m_Speed = 0;
	float m_TurboScale = 0;
	float m_JumpPower = 0;
	float m_Angle = 0;
	float m_TurboStamina = 0;
	float m_StaminaConsumption = 0;
	float m_StaminaRecovery = 0;
	float m_StaminaMax = 0;
	float m_DefDrag = 0;

	bool m_Axel = false;
	bool m_Turbo = false;
	bool m_StaminaEmpty = false;
	bool m_Back = false;
	bool m_RightTurn = false;
	bool m_LeftTurn = false;
	bool m_IsGround = false;

	enum class CarState
	{
		Ground,
		Sky,
		Landing
	};

	class CarUpdate
	{
	public:
		CarUpdate() {}
		virtual ~CarUpdate() {}

		virtual void Update(CarControl* cc);
		virtual void Jump(CarControl* cc);
	};

	class CarSkyUpdate : public CarUpdate
	{
	public:
		CarSkyUpdate() :CarUpdate() {}

		void Update(CarControl* cc) override;
		void Jump(CarControl* cc) override;

	private:
		void Dodge(CarControl* cc,D3DXVECTOR3 axis);

		bool doubleJump = true;
		bool jumpTrigger = false;
	};

	class CarLandingUpdate : public CarUpdate
	{
	public:
		CarLandingUpdate() :CarUpdate() {}

		void Update(CarControl* cc) override;
		void Jump(CarControl* cc) override {}
	};


	void ChangeState(CarState state);
	CarUpdate* m_CU = nullptr;
	CarUpdate* m_CUtmp = nullptr;
};
