#pragma once
#include "component.h"

class ParticleSystem : public Component
{
public:
	ParticleSystem(class GameObject* go):Component(go){}

	virtual void Init() override {}
	virtual void Uninit() override{}
	virtual void Update() override
	{
		m_FrameCount++;
		if (m_SpawnFrame <= m_FrameCount) m_FrameCount = 0;
	}
	virtual void Draw() override{}
	
	void SetAmountPerSecond(float aps)
	{ 
		m_AmountPerSecond = aps;
		if (m_AmountPerSecond > 0)
		{
			m_SpawnFrame = (int)(60 / m_AmountPerSecond);
		}
	}
	void SetPositionOffset(D3DXVECTOR3 offset) { m_PositionOffset = offset; }
	void SetLifetime(int lifetime) { m_ParticleLifetime = lifetime; }
	void SetSpawnPoint(D3DXVECTOR3 position) { m_SpawnPoint = position; }
	void SetParticleVelocity(D3DXVECTOR3 velocity) { m_ParticleVelocity = velocity; }
	void SetParticleSize(D3DXVECTOR3 size) { m_ParticleSize = size; }
	void SetParticleColor(D3DXCOLOR color) { m_ParticleColor = color; }

protected:
	void SpawnParticle(int layer);

	int GetFrameCount() { return m_FrameCount; }

	D3DXVECTOR3 m_PositionOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_ParticleLifetime = 60;
	D3DXVECTOR3 m_SpawnPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_ParticleVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_ParticleSize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXCOLOR m_ParticleColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
private:
	float m_AmountPerSecond = 0.0f;
	int m_SpawnFrame = 0;
	int m_FrameCount = 0;
};