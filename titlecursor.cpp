#include "main.h"
#include "manager.h"
#include "titlecursor.h"
#include "titleparticle.h"
#include "tool.h"
#include "audio.h"

void TitleCursor::Init()
{
	GameObject::Init();

	transform->m_Position = Tool::ORIGIN;

	for (int i = 0; i < 2; i++)
	{
		m_Particle[i] = AddComponent<TitleParticle>();
		m_Particle[i]->SetDivide(8);
		m_Particle[i]->SetRadius(50);
		m_Particle[i]->SetParticleSize(D3DXVECTOR3(20.0f, 20.0f, 0.0f));
		m_Particle[i]->SetParticleColor(D3DXCOLOR(0.3f, 0.3f, 1.0f, 0.4f));
		m_Particle[i]->SetLifetime(30);
	}

	m_Particle[0]->SetPositionOffset(D3DXVECTOR3(40.0f, 0.0f, 0.0f));
	m_Particle[0]->SetParticleVelocity(D3DXVECTOR3(3.0f, 0.0f, 0.0f));

	m_Particle[1]->SetPositionOffset(D3DXVECTOR3(-40.0f, 0.0f, 0.0f));
	m_Particle[1]->SetParticleVelocity(D3DXVECTOR3(-3.0f, 0.0f, 0.0f));


}

void TitleCursor::Uninit()
{
	GameObject::Uninit();
}

void TitleCursor::Update()
{
	GameObject::Update();
}

void TitleCursor::Draw()
{
	GameObject::Draw();
}