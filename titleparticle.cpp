#include "main.h"
#include "titleparticle.h"
#include "tool.h"
#include "gameObject.h"
#include "particle.h"

void TitleParticle::Init()
{
	ParticleSystem::Init();
	SetAmountPerSecond(30.0f);
	radius = 10.0f;
	m_ParticleSize = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
}

void TitleParticle::Uninit()
{
	ParticleSystem::Uninit();
}

void TitleParticle::Update()
{
	ParticleSystem::Update();
	if (GetFrameCount() == 0)
	{
		D3DXVECTOR2 randvec = Tool::RandVec2D(divide, 0.0f);
		m_SpawnPoint = gameObject->GetTransform()->m_Position + (D3DXVECTOR3(randvec.x, randvec.y, 0.0f) * radius);
		SpawnParticle(2);
	}
}

void TitleParticle::Draw()
{
	ParticleSystem::Draw();
}