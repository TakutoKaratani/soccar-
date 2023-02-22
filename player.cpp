#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "input.h"
#include "audio.h"
#include "drawmodel.h"
#include "rigidbody.h"
#include "Field.h"
#include "carcontrol.h"
#include "turboparticle.h"
#include "gamelight.h"

void Player::Init()
{
	GameObject::Init();
	DrawModel* dm = AddComponent<DrawModel>();
	dm->Load("asset\\model\\boxelcar.obj");
	dm->SetShader("depthShadowMappingVS.cso", "depthShadowMappingPS.cso");

	m_DepthShadow = true;

	m_rb = AddComponent<Rigidbody>();
	m_rb->SetDrag(8.0f);
	m_rb->SetMass(2.0f);
	AddComponent<CarControl>();
	AddComponent<TurboParticle>();

	transform->m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	transform->m_Scale = D3DXVECTOR3(1.8f, 1.8f, 1.8f);
}

void Player::Uninit()
{
	GameObject::Uninit();
}

void Player::Update()
{
	GameObject::Update();

	float groundHeight = 0.0f;

	if (transform->m_Position.y < groundHeight + transform->m_Scale.y * 0.5f)
	{
		if (m_rb->velocity.y <= 0)
		{
			CarControl* cc = GetComponent<CarControl>();
			if (cc) cc->Landing();
			transform->m_Position.y = groundHeight + transform->m_Scale.y * 0.5f;
			m_rb->velocity.y = 0.0f;
		}
	}


	Light* light = Manager::GetInstance()->GetScene()->GetGameObject<GameLight>();
	if (light)
	{
		light->SetPosition(transform->m_Position);
		light->SetAt(transform->m_Position);
	}
}

void Player::Draw()
{
	GameObject::Draw();
}

D3DXVECTOR3 Player::GetVelocity()
{
	return m_rb->velocity;
}
