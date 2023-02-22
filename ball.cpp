#include "main.h"
#include "manager.h"
#include "scene.h"
#include "ball.h"
#include "drawmodel.h"
#include "tool.h"
#include "player.h"
#include "Enemy.h"
#include "rigidbody.h"
#include "audio.h"

void Ball::Init()
{
	GameObject::Init();
	DrawModel* dm = AddComponent<DrawModel>();
	dm->Load("asset\\model\\soccerball3.obj");
	dm->SetShader("depthShadowMappingVS.cso", "depthShadowMappingPS.cso");
	m_rb = AddComponent<Rigidbody>();
	m_rb->SetDrag(2.0f);
	m_rb->SetMass(0.5f);

	m_DepthShadow = true;

	transform->m_Position = D3DXVECTOR3(4.0f, 0.5f, 5.0f);
	transform->m_Scale = D3DXVECTOR3(4.f, 4.f, 4.f);

	m_SE = Manager::GetInstance()->GetScene()->AddGameObject<Audio>(0);
	m_SE->Load("asset\\sound\\kick.wav");
}

void Ball::Uninit()
{
	GameObject::Uninit();
}

void Ball::Update()
{
	GameObject::Update();

	float rotate = m_rb->GetVelocityLength() * 0.25f;
	if (rotate < 0.003f) rotate = 0;
	transform->MulQuaternion(m_RotationAxis, rotate);

	if (transform->m_Position.y < 0 + transform->m_Scale.y * 0.5f)
	{
		transform->m_Position.y = transform->m_Scale.y * 0.5f;
		if (m_rb->velocity.y < -0.1f)
		{
			m_rb->AddForce(D3DXVECTOR3(0.0f, -m_rb->velocity.y * 0.9f, 0.0f), ForceMode::Impulse);
			KickSound();
		}
		else
		{
			m_rb->velocity.y = 0;
		}
	}

	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	if (player)
	{
		HitChack(player); 
	}

	Enemy* enemy = scene->GetGameObject<Enemy>();

	if (enemy)
	{
		HitChack(enemy);
	}

	if (transform->m_Position.z > 210 - transform->m_Scale.z * 0.5f)
	{
		transform->m_Position.z = 210 - transform->m_Scale.z * 0.5f;
		m_rb->velocity.z *= -1;
	}
	if (transform->m_Position.z < -210 + transform->m_Scale.z * 0.5f)
	{
		transform->m_Position.z = -210 + transform->m_Scale.z * 0.5f;
		m_rb->velocity.z *= -1;
	}


	if (transform->m_Position.x > 100 - transform->m_Scale.x * 0.5f)
	{
		transform->m_Position.x = 100 - transform->m_Scale.x * 0.5f;
		m_rb->velocity.x *= -1;
	}
	if (transform->m_Position.x < -100 + transform->m_Scale.x * 0.5f)
	{
		transform->m_Position.x = -100 + transform->m_Scale.x * 0.5f;
		m_rb->velocity.x *= -1;
	}

}

void Ball::Draw()
{
	GameObject::Draw();
}

void Ball::HitChack(GameObject* car)
{
	D3DXVECTOR3 back;
	Transform* offset = new Transform(nullptr);
	offset->SetScale(D3DXVECTOR3(1.0f, 1.3f, 1.5f));
	if (Tool::CollisionOBBAndSphere(car->GetTransform(), offset, transform->m_Position, transform->m_Scale.x * 0.5f, back))
	{
		Kick(car, back);
	}
	delete offset;
	offset = nullptr;
}

void Ball::Kick(GameObject* car,D3DXVECTOR3 back)
{
	if (transform->m_Position.y + back.y < 0 + transform->m_Scale.y * 0.5f)
	{
		back.y = 0;
	}

	D3DXVec3Normalize(&back, &back);
	D3DXVECTOR3 dir = transform->m_Position - car->GetPosition();
	D3DXVec3Normalize(&dir, &dir);
	D3DXVECTOR3 vec = back + dir;
	D3DXVec3Normalize(&vec, &vec);

	Rigidbody* carRb = car->GetComponent<Rigidbody>();
	if (!carRb) return;
	D3DXVECTOR3 carvel = carRb->velocity;
	vec.y += carvel.y + Tool::Vec2Length(D3DXVECTOR2(carvel.x, carvel.z)) * 0.2f;

	vec *= Tool::Vec3Dot(carvel, vec) * 0.75f;

	float len = Tool::Vec3Length(vec);

	float maxVecLen = 0.7f;
	if (len > maxVecLen)
	{
		float r = maxVecLen / len;
		vec *= r;
	}

	m_RotationAxis = Tool::Vec3Normalize(Tool::Vec3Cross(carvel, vec));

	m_rb->AddForce(vec, ForceMode::Impulse);
	KickSound();
}

void Ball::KickSound()
{
	D3DXVECTOR3 campos = Manager::GetInstance()->GetScene()->GetMainCamera()->GetPosition();

	float distance = Tool::Vec3Length(campos - GetPosition());
	float soundspace = 100.0f;

	if (distance >= soundspace) return;

	float ratio = soundspace - distance;

	m_SE->SetVolume((ratio / soundspace) * 0.2f);
	m_SE->Play();
}