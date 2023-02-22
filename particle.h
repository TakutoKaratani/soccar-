#pragma once
#include "gameObject.h"
class Particle : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	class DrawSprite* GetDrawSprite() { return m_ds; }

	void SetTexture(const char* filename);
	void SetStatus(int lifetime,D3DXVECTOR3 position, D3DXVECTOR3 velocity, D3DXVECTOR3 size, D3DXCOLOR color);
	void UseGravity();
	void SetDrag(float drag);

protected:
	class DrawSprite* m_ds = nullptr;
	class Rigidbody* m_rb = nullptr;
};
