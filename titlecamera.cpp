#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "titlecamera.h"

void TitleCamera::Init()
{
	GameObject::Init();
	transform->m_Position = D3DXVECTOR3(3.0f, 4.0f, 7.0f);
	m_at = D3DXVECTOR3(3.0f, 0.0f, 0.0f);
}