#include "main.h"
#include "rigidbody.h"
#include "gameObject.h"
#include "transform.h"

const float Rigidbody::massMin = 0.000001f;
float d = 0.5f;
float delta = 0.0166f * d;
const float Rigidbody::gravity = 9.8f * delta * d * 0.3f;

void Rigidbody::Init()
{
	Gravity(true);
}

void Rigidbody::Uninit()
{
	delete gravityUpdate;
}

void Rigidbody::Update()
{
	if (isKinematic) return;
	gravityUpdate->Update(this);
}

void Rigidbody::AddForce(D3DXVECTOR3 force, ForceMode mode)
{
	switch (mode)
	{
	case ForceMode::Force:
		velocity += force / mass * delta;
		break;
	case ForceMode::Acceleration:
		velocity += force * delta;
		break;
	case ForceMode::Impulse:
		velocity += force / mass;
		break;
	case ForceMode::VelocityChange:
		velocity += force;
		break;
	default:
		velocity += force / mass * delta;
		break;
	}
}

void Rigidbody::Gravity(bool use)
{
	useGravity = use;

	if (gravityUpdate)
	{
		delete gravityUpdate;
	}

	if (use)
	{
		gravityUpdate = new GravityUpdate();
	}
	else
	{
		gravityUpdate = new NoGravityUpdate();
	}
}

float Rigidbody::GetVelocityLength()
{
	return sqrtf(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
}


void GravityUpdate::Update(Rigidbody* rb)
{
	Transform* tf = rb->gameObject->GetTransform();

	Constraints con = rb->constraints;
	if (!con.position.x)
	{
		tf->m_Position.x += rb->velocity.x;
	}
	if (!con.position.y)
	{
		tf->m_Position.y += rb->velocity.y;
	}
	if (!con.position.z)
	{
		tf->m_Position.z += rb->velocity.z;
	}

	D3DXVECTOR3 v = rb->velocity;
	float d = rb->GetDrag();

	v.x -= v.x * d * delta;
	v.y -= (v.y * d * delta) + (Rigidbody::gravity * rb->GetMass());
	v.z -= v.z * d * delta;

	rb->velocity = v;
	
}

void NoGravityUpdate::Update(Rigidbody* rb)
{
	Transform* tf = rb->gameObject->GetTransform();

	Constraints con = rb->constraints;
	if (!con.position.x)
	{
		tf->m_Position.x += rb->velocity.x;
	}
	if (!con.position.y)
	{
		tf->m_Position.y += rb->velocity.y;
	}
	if (!con.position.z)
	{
		tf->m_Position.z += rb->velocity.z;
	}

	D3DXVECTOR3 v = rb->velocity;
	float d = rb->GetDrag();

	v.x -= v.x * d * delta;
	v.y -= v.y * d * delta;
	v.z -= v.z * d * delta;

	rb->velocity = v;
}

