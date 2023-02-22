#pragma once
#include "gameObject.h"

class Model;

class Player : public GameObject
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	D3DXVECTOR3 GetVelocity();

private:
	class Rigidbody* m_rb = nullptr;
};
