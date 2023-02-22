#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"
#include "player.h"
#include "input.h"
#include <cmath>

void Camera::Init()
{
	GameObject::Init();
	transform->m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_offset = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	m_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	m_fov = 1.0f;
}

void Camera::Uninit()
{
	GameObject::Uninit();
}

void Camera::Update()
{
	GameObject::Update();
}

void Camera::Draw()
{
	GameObject::Draw();

	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &transform->m_Position, &m_at, &up);
	Renderer::GetInstance()->SetViewMatrix(&m_ViewMatrix);

	D3DXMATRIX mtxProjection;
	D3DXMatrixPerspectiveFovLH(&mtxProjection, m_fov, m_aspect, 1.0f, 3000.0f);

	Renderer::GetInstance()->SetProjectionMatrix(&mtxProjection);
}

D3DXVECTOR3 Camera::GetVec()
{
	float x, y, z;
	x = m_at.x - transform->m_Position.x;
	y = m_at.y - transform->m_Position.y;
	z = m_at.z - transform->m_Position.z;
	float a = sqrtf(x * x + y * y + z * z);
	D3DXVECTOR3 camVec = D3DXVECTOR3(x / a, y / a, z / a);

	return camVec;
}

D3DXVECTOR3 Camera::GetVecRight()
{
	float x, z;
	x = m_at.x - transform->m_Position.x;
	z = m_at.z - transform->m_Position.z;
	float a = sqrtf(x * x + z * z);
	D3DXVECTOR3 camVec = D3DXVECTOR3(z / a, 0.0f, -x / a);

	return camVec;
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
	transform->m_Position = pos;
}
