#include "main.h"
#include "particlesystem.h"
#include "manager.h"
#include "particle.h"
#include "drawSprite.h"

void ParticleSystem::SpawnParticle(int layer)
{
	if (layer == 2 || layer == 3)
	{
		Particle* particle = Manager::GetInstance()->GetScene()->AddGameObject<Particle>(layer);
		particle->SetStatus(m_ParticleLifetime, m_SpawnPoint, m_ParticleVelocity, m_ParticleSize, m_ParticleColor);
	}
	else if (layer == 1)
	{
		Particle* particle = Manager::GetInstance()->GetScene()->AddGameObject<Particle>(layer);
		particle->GetDrawSprite()->SetMode(DrawSprite::DRAW_MODE::MODE_3D_BILLBOARD_EDIT);
		particle->SetStatus(m_ParticleLifetime, m_SpawnPoint + m_PositionOffset, m_ParticleVelocity, m_ParticleSize, m_ParticleColor);
	}
}