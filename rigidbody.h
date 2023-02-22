#pragma once
#include "component.h"

class Constraint
{
public:
	bool x = false;
	bool y = false;
	bool z = false;

	void FreezeAll() { x = true; y = true; z = true; }
	void DefrostAll() { x = false; y = false; z = false; }
};

class Constraints
{
public:
	Constraint position;
	Constraint rotation;

	void FreezeAll() {
		position.FreezeAll();
		rotation.FreezeAll();
	}
	void DefrostAll() { 
		position.DefrostAll();
		rotation.DefrostAll();
	}
};

enum ForceMode
{
	Force,
	Acceleration,
	Impulse,
	VelocityChange,
};

class Rigidbody : public Component
{
public:
	Rigidbody(class GameObject* go) : Component(go){}

	void Init();
	void Uninit();
	void Update();

	void AddForce(D3DXVECTOR3 force, ForceMode mode);

	void SetMass(float m) {
		if (m < massMin)
		{
			m = massMin;
		}
		mass = m;
	}
	float GetMass() const { return mass; }
	void SetDrag(float d) { drag = d; }
	float GetDrag() const { return drag; }
	void Gravity(bool use);
	void Kinematic(bool is) { isKinematic = is; }
	
	float GetVelocityLength();

	static const float massMin;
	static const float gravity;

	D3DXVECTOR3 velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Constraints constraints;

private:
	float mass = 1.0f;
	bool useGravity = true;
	bool isKinematic = false;
	float drag = 0.0f;

	class GravityUpdate* gravityUpdate = nullptr;
};

class GravityUpdate
{
public:
	virtual void Update(Rigidbody* rb);
};

class NoGravityUpdate : public GravityUpdate
{
public:
	void Update(Rigidbody* rb) override;
};

