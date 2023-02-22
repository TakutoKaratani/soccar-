#pragma once
#include "gameObject.h"

class Ball : public GameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void KickSound();

private:
	void HitChack(GameObject* car);
	void Kick(GameObject* car,D3DXVECTOR3 back);

	class Audio* m_SE = nullptr;
	class Rigidbody* m_rb = nullptr;
	D3DXVECTOR3 m_RotationAxis = { 1.0f,0.0f,0.0f };
};
