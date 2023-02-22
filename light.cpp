#include "main.h"
#include "renderer.h"
#include "light.h"

void Light::Init()
{
	GameObject::Init();
	m_Light.Enable = true;
	m_Light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_Light.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	transform->m_Position = { 10.0f,10.0f,10.0f };
	m_at = { 0.0f,0.0f,0.0f };

	m_near = 1.0f;
	m_far = 40.0f;
}

void Light::SetLight()
{
	D3DXVECTOR3 dir = m_at - transform->m_Position;
	m_Light.Direction = D3DXVECTOR4(dir.x, dir.y, dir.z, 0.0f);
	D3DXVec4Normalize(&m_Light.Direction, &m_Light.Direction);
	D3DXMatrixLookAtLH(&m_Light.ViewMatrix, &transform->m_Position, &m_at, &Transform::up);
	D3DXMatrixPerspectiveFovLH(&m_Light.ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, m_near, m_far);
	Renderer::GetInstance()->SetLight(m_Light);
	Renderer::GetInstance()->SetViewMatrix(&m_Light.ViewMatrix);
	Renderer::GetInstance()->SetProjectionMatrix(&m_Light.ProjectionMatrix);
}