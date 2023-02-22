#include "main.h"
#include "turboparticle.h"
#include "tool.h"
#include "gameObject.h"
#include "particle.h"

void TurboParticle::Init()
{
	ParticleSystem::Init();
	SetAmountPerSecond(20.0f);
	m_ParticleSize = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	m_ParticleColor = D3DXCOLOR(1.0f, 0.6f, 0.0f, 0.6f);
	m_ParticleLifetime = 20;
}

void TurboParticle::Uninit()
{
	ParticleSystem::Uninit();
}

void TurboParticle::Update()
{
	ParticleSystem::Update();
	if (GetFrameCount() == 0 && m_Active)
	{
		m_SpawnPoint = gameObject->GetPosition() + (-gameObject->GetForward() * (gameObject->GetScale().z * 0.5f) + (-gameObject->GetUp() * (gameObject->GetScale().y * 0.4f)));
		D3DXVECTOR3 atPos = m_SpawnPoint - gameObject->GetForward() + Tool::RandVec3D(0.5f);
		m_ParticleVelocity = (atPos - m_SpawnPoint) * 0.05f;
		SpawnParticle(1);
	}
	m_Active = false;
}

void TurboParticle::Draw()
{
	ParticleSystem::Draw();
}
