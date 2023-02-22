#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "dioramacamera.h"
#include "input.h"

void DioramaCamera::Init()
{
	GameObject::Init();
	transform->m_Position = D3DXVECTOR3(0.0f, 1.8f, 3.5f);
	m_at = D3DXVECTOR3(0.0f, 2.f, 0.0f);
}

void DioramaCamera::Uninit()
{
	GameObject::Uninit();
}

void DioramaCamera::Update()
{
	GameObject::Update();
	D3DXVECTOR3 currentPos = GetPosition();

	float speed = -0.00f + ((Input::GetCursolPos().x - (SCREEN_WIDTH * 0.5f)) * 0.05f) / 60;

	transform->m_Position.x = currentPos.x * cosf(speed) + currentPos.z * sinf(speed);
	transform->m_Position.z = -currentPos.x * sinf(speed) + currentPos.z * cosf(speed);
}