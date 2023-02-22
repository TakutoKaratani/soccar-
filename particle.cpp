#include "main.h"
#include "renderer.h"
#include "particle.h"
#include "texturemanager.h"
#include "drawSprite.h"
#include "rigidbody.h"
#include "tool.h"

void Particle::Init()
{
	GameObject::Init();
	transform->m_Position = Tool::ORIGIN;
	transform->SetScale(D3DXVECTOR3(10.0f, 10.0f, 0.0f));

	m_ds = AddComponent<DrawSprite>();
	m_ds->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	m_ds->SetMode(DrawSprite::DRAW_MODE::MODE_2D_EDIT);
	m_ds->Load("asset/texture/white.png");

	m_rb = AddComponent<Rigidbody>();
	m_rb->Gravity(false);
	m_rb->SetDrag(0.0f);
}

void Particle::Uninit()
{
	GameObject::Uninit();
}

void Particle::Update()
{
	GameObject::Update();
}

void Particle::Draw()
{
	GameObject::Draw();
}

void Particle::SetTexture(const char* filename)
{
	m_ds->Load(filename);
}

void Particle::SetStatus(int lifetime, D3DXVECTOR3 position,D3DXVECTOR3 velocity, D3DXVECTOR3 size, D3DXCOLOR color)
{
	SetDestroy(lifetime);
	transform->m_Position = position;
	transform->m_Scale = size;
	m_rb->AddForce(velocity, ForceMode::VelocityChange);
	m_ds->SetColor(color);
}

void Particle::UseGravity()
{
	m_rb->Gravity(true);
}

void Particle::SetDrag(float drag)
{
	m_rb->SetDrag(drag);
}