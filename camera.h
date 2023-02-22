#pragma once
#include "gameObject.h"

class Camera : public GameObject
{
public:
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	D3DXVECTOR3 GetVec();
	D3DXVECTOR3 GetVecRight();

	void SetTargetPos(D3DXVECTOR3 targetPos) { m_at = targetPos; }
	void SetFov(float fov) { m_fov = fov; }
	void SetPosition(D3DXVECTOR3 pos);

protected:
	D3DXMATRIX m_ViewMatrix;

	D3DXVECTOR3 m_offset;
	D3DXVECTOR3 m_at;

	float m_aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	float m_fov = 1.0f;
};