#include "main.h"
#include "renderer.h"
#include "gamelight.h"

void GameLight::Init()
{
	Light::Init();
	m_offset = { 20.0f,20.0f,20.0f };

	m_near = 15.0f;
	m_far = 50.0f;
}

void GameLight::SetLight()
{
	D3DXVECTOR3 eye = transform->m_Position + m_offset;
	D3DXVECTOR3 dir = m_at - eye;
	m_Light.Direction = D3DXVECTOR4(dir.x, dir.y, dir.z, 0.0f);
	D3DXVec4Normalize(&m_Light.Direction, &m_Light.Direction);
	D3DXMatrixLookAtLH(&m_Light.ViewMatrix, &eye, &m_at, &Transform::up);
	D3DXMatrixPerspectiveFovLH(&m_Light.ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, m_near, m_far);
	Renderer::GetInstance()->SetLight(m_Light);
	Renderer::GetInstance()->SetViewMatrix(&m_Light.ViewMatrix);
	Renderer::GetInstance()->SetProjectionMatrix(&m_Light.ProjectionMatrix);
}