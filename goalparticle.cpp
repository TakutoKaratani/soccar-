#include "main.h"
#include "manager.h"
#include "goalparticle.h"
#include "circleparticle.h"
#include "drawSprite.h"
#include "tool.h"

void GoalParticle::Init()
{
	ParticleSystem::Init();
	burstAmount = 100;
	m_ParticleSize = D3DXVECTOR3(0.6f, 0.6f, 0.6f);
	m_ParticleColor = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f);
	m_ParticleLifetime = 120;
}

void GoalParticle::Active()
{
	if (on) return;
	on = true;
	m_SpawnPoint = gameObject->GetPosition();
	m_PositionOffset = D3DXVECTOR3(0.0f, gameObject->GetScale().y, 0.0f);
	for (int i = 0; i < burstAmount; i++)
	{
		m_ParticleVelocity = Tool::RandVec3D(0.5f);
		Particle* particle;
		if (i % 2 == 0)
		{
			particle = Manager::GetInstance()->GetScene()->AddGameObject<CircleParticle>(1);
			m_ParticleColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
			m_ParticleSize = D3DXVECTOR3(0.4f, 0.4f, 0.4f);
		}
		else
		{
			particle = Manager::GetInstance()->GetScene()->AddGameObject<Particle>(1);
			m_ParticleColor = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f);
			m_ParticleSize = D3DXVECTOR3(0.6f, 0.6f, 0.6f);
		}
		particle->GetDrawSprite()->SetMode(DrawSprite::DRAW_MODE::MODE_3D_BILLBOARD_EDIT);
		particle->SetDrag(2.0f);
		particle->SetStatus(m_ParticleLifetime, m_SpawnPoint + m_PositionOffset, m_ParticleVelocity, m_ParticleSize, m_ParticleColor);
	}
}
